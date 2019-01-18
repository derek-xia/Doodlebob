#include <ctime>
#include <cstdlib>
#include "server.h"

using namespace std;
using namespace Game;

string PickWord()
{
  ifstream words_file;
  string line;
  vector<string> words_list;

  words_file.open("words.txt");
  if (!words_file) {
    return "Couldn't find file";
  }

  while (getline(words_file, line)) {
    words_list.push_back(line);
  }
  words_file.close();

  srand(time(nullptr));
  int ind = rand() % words_list.size();
  return words_list[ind];
}

string PickHint(string hint, string word)
{
  int empty_count = 0;
  for (char c : hint) {
    if (c == '_') {
      empty_count++;
    }
  }
  if (empty_count == 0) {
    return "";
  }
  srand(time(nullptr));
  int ind = rand() % empty_count;

  int empty_ind = 0;
  for (int i = 0; i < hint.length(); i++) {
    if (hint[i] == '_') {
      if (empty_ind == ind) {
        hint[i] = word[i];
        return hint;
      }
      empty_ind++;
    }
  }
  return hint;
}

int GameStateI::GetTimeRemaining()
{
  return kTurnLength_ - ((time(nullptr) - game_.start_time_) % kTurnLength_);
}

void GameStateI::ChangeTurn(GameInfo &info)
{
  if (game_.round_ == 0) {
    game_.player_turn_ = 0;
    info.currplayer = 0;
  }
  if (game_.player_turn_ == 0) {
    game_.start_time_ = time(nullptr);
    game_.round_++;
    info.round = game_.round_;
  }
  
  // Clears panel
  game_.lines_.clear();
  game_.colors_.clear();
  
  // Resets player guesses
  for (Player p : game_.players_) {
    p.guessed = false;
    p.lastguess = "";
  }
  // Picks new word
  game_.word_ = PickWord();
  info.changedturn = true;
  std::cout << info.currplayer << "'s turn" << std::endl;
  std::cout << "Chose word " << game_.word_ << std::endl;

  // Sets hint to underscores
  game_.hint_.clear();
  game_.hint_.resize(game_.word_.length());
  for (int i = 0; i < game_.word_.length(); i++) {
    if (game_.word_[i] == ' ') {
      game_.hint_[i] = ' ';
    } else {
      game_.hint_[i] = '_';
    }
  }
}

void
GameStateI::printString(string s, const Ice::Current&)
{
  cout << s + '\n' << endl;
}

int GameStateI::AddPlayer(string name, const Ice::Current&) {
  int id = game_.players_.size();
  Player player;
  player.score = 0;
  player.guessed = false;
  player.lastguess = "";
  player.name = name;
  game_.players_.push_back(player);
  if (id == 0) {
    game_.start_time_ = time(nullptr) - 1;
    game_.round_ = 0;
    game_.word_ = "";
    game_.hint_ = "";
  }
  cout << "Added player " << id << endl;
  return id;
}

void GameStateI::IncrementScore(int id, const Ice::Current&) {
  game_.players_[id].score++;
  cout << "Incremented player " << id << endl;
}

int GameStateI::GetScore(int id, const Ice::Current&) {
  return game_.players_[id].score;
}

int GameStateI::GetNumPlayers(const Ice::Current&) {
  return game_.players_.size();
}

LineVector GameStateI::GetLines(const Ice::Current&)
{
  return game_.lines_;
}

void GameStateI::DrawLines(LineVector lines, const Ice::Current&)
{
  game_.lines_ = lines;
}

ColorVector GameStateI::GetColors(const Ice::Current &)
{
  return game_.colors_;
}

void GameStateI::DrawColors(ColorVector colors, const Ice::Current &)
{
  game_.colors_ = colors;
}

GameInfo GameStateI::GetGameInfo(const Ice::Current &)
{
  GameInfo info;
  info.inprogress = true;
  info.numplayers = game_.players_.size();
  info.currplayer = ((time(nullptr) - game_.start_time_) / kTurnLength_) % info.numplayers;
  info.changedturn = false;
  info.time = GetTimeRemaining();
  info.round = game_.round_;

  // Switches the turn
  if (info.currplayer != game_.player_turn_) {
    game_.player_turn_ = info.currplayer;
    ChangeTurn(info);
  }
  if (game_.word_.length() != 0) {
    if (!game_.hint_given_ && (GetTimeRemaining() % (kTurnLength_ / (game_.word_.length() / 2)) == 0)) {
      game_.hint_given_ = true;
      game_.hint_ = PickHint(game_.hint_, game_.word_);
    } else if (game_.hint_given_ && (GetTimeRemaining() % (kTurnLength_ / (game_.word_.length() / 2)) != 0)) {
      game_.hint_given_ = false;
    }
  }

  info.hint = game_.hint_;
  info.word = game_.word_;

  return info;
}

bool GameStateI::CheckWord(string word, int id, const Ice::Current &)
{
  // Returns false if the word is incorrect
  if (word.length() != game_.word_.length()) {
    return false;
  }
  for (size_t i = 0; i < word.length(); i++) {
    if (tolower(word[i]) != tolower(game_.word_[i])) {
      return false;
    }
  }
  // Otherwise, returns true and increments players' score
  game_.players_[id].guessed = true;
  game_.players_[id].score += GetTimeRemaining() * 10 / kTurnLength_ * 10;
  game_.players_[game_.player_turn_].score += GetTimeRemaining() * 10 / kTurnLength_ * 5;
  return true;
}

Players GameStateI::GetPlayers(const::Ice::Current & current)
{
  return game_.players_;
}

int main(int argc, char* argv[])
{
  try
  {
    Ice::CommunicatorHolder ich(argc, argv);
    auto adapter = ich->createObjectAdapterWithEndpoints("GameServerAdapter", "default -p 10000");
    auto servant = make_shared<GameStateI>();
    adapter->add(servant, Ice::stringToIdentity("GameServer"));
    adapter->activate();
    ich->waitForShutdown();
  }
  catch (const std::exception& e)
  {
    cerr << e.what() << endl;
    return 1;
  }
  return 0;
}