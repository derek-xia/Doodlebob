#include "client.h"
#include "Game.h"

using std::vector;

int Client::Connect(std::string name)
{
  try
  {
    int argc;
    char* argv[1];
    Ice::CommunicatorHolder ich(argc,argv);

    std::cout << "connect attempt" << std::endl;
    auto base = ich->stringToProxy(kProxy_);
    auto gamestate = Ice::checkedCast<Game::GameStatePrx>(base);
    if (!gamestate)
    {
      throw std::runtime_error("Invalid proxy");
    }

    std::cout << "connect finished" << std::endl;
    gamestate->printString("Added GUI player");
    id_ = gamestate->AddPlayer(name); // Adds itself to the server
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}

void Client::Increment()
{
  try
  {
    int argc;
    char* argv[1];
    Ice::CommunicatorHolder ich(argc, argv);

    std::cout << "connect" << std::endl;
    auto base = ich->stringToProxy(kProxy_);
    auto gamestate = Ice::checkedCast<Game::GameStatePrx>(base);
    if (!gamestate)
    {
      throw std::runtime_error("Invalid proxy");
    }
    gamestate->IncrementScore(id_);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return;
  }
}

void Client::SetNumPlayers()
{
  try
  {
    int argc;
    char* argv[1];
    Ice::CommunicatorHolder ich(argc, argv);

    auto base = ich->stringToProxy(kProxy_);
    auto gamestate = Ice::checkedCast<Game::GameStatePrx>(base);
    if (!gamestate)
    {
      throw std::runtime_error("Invalid proxy");
    }

    num_players_ = gamestate->GetNumPlayers();
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return;
  }
}

int Client::getId()
{
  return id_;
}

void Client::SetLines(std::vector<ofPolyline> lines)
{
  try
  {
    int argc;
    char* argv[1];
    Ice::CommunicatorHolder ich(argc, argv);

    auto base = ich->stringToProxy(kProxy_);
    auto gamestate = Ice::checkedCast<Game::GameStatePrx>(base);
    if (!gamestate)
    {
      throw std::runtime_error("Invalid proxy");
    }

    vector<vector<Game::Pair>> linevector;
    for (ofPolyline line : lines) {
      linevector.push_back(vector<Game::Pair>());
      for (ofVec2f vertex : line.getVertices()) {
        Game::Pair point;
        point.x = vertex.x;
        point.y = vertex.y;
        linevector[linevector.size() - 1].push_back(point);
      }
    }
    gamestate->DrawLines(linevector);

  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

std::vector<ofPolyline> Client::GetLines()
{
  try
  {
    int argc;
    char* argv[1];
    Ice::CommunicatorHolder ich(argc, argv);

    auto base = ich->stringToProxy(kProxy_);
    auto gamestate = Ice::checkedCast<Game::GameStatePrx>(base);
    if (!gamestate)
    {
      throw std::runtime_error("Invalid proxy");
    }

    Game::LineVector lines = gamestate->GetLines();
    vector<ofPolyline> polylines;
    for (Game::Line line : lines) {
      polylines.push_back(ofPolyline());
      for (Game::Pair pair : line) {
        polylines[polylines.size() - 1].addVertex(pair.x, pair.y);
      }
    }
    return polylines;

  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

void Client::SetColors(std::vector<int> colors)
{
  try
  {
    int argc;
    char* argv[1];
    Ice::CommunicatorHolder ich(argc, argv);

    auto base = ich->stringToProxy(kProxy_);
    auto gamestate = Ice::checkedCast<Game::GameStatePrx>(base);
    if (!gamestate)
    {
      throw std::runtime_error("Invalid proxy");
    }
    gamestate->DrawColors(colors);

  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

std::vector<int> Client::GetColors()
{
  try
  {
    int argc;
    char* argv[1];
    Ice::CommunicatorHolder ich(argc, argv);

    auto base = ich->stringToProxy(kProxy_);
    auto gamestate = Ice::checkedCast<Game::GameStatePrx>(base);
    if (!gamestate)
    {
      throw std::runtime_error("Invalid proxy");
    }

    Game::ColorVector lines = gamestate->GetColors();
    return lines;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

void Client::UpdateGameInfo()
{
  try
  {
    int argc;
    char* argv[1];
    Ice::CommunicatorHolder ich(argc, argv);

    auto base = ich->stringToProxy(kProxy_);
    auto gamestate = Ice::checkedCast<Game::GameStatePrx>(base);
    if (!gamestate)
    {
      throw std::runtime_error("Invalid proxy");
    }

    state_ = gamestate->GetGameInfo();

  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

int Client::GetCurrPlayer()
{
  return state_.currplayer;
}

bool Client::IsInProgress()
{
  return state_.inprogress;
}

bool Client::HasChangedTurn()
{
  return state_.changedturn;
}

std::string Client::GetWord()
{
  return state_.word;
}

std::string Client::GetHint()
{
  return state_.hint;
}

int Client::GetTime()
{
  return state_.time;
}

int Client::GetRound()
{
  return state_.round;
}

bool Client::CheckWord(string word)
{
  try
  {
    int argc;
    char* argv[1];
    Ice::CommunicatorHolder ich(argc, argv);

    auto base = ich->stringToProxy(kProxy_);
    auto gamestate = Ice::checkedCast<Game::GameStatePrx>(base);
    if (!gamestate)
    {
      throw std::runtime_error("Invalid proxy");
    }

    return gamestate->CheckWord(word, id_);

  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return false;
  }
}

void Client::UpdatePlayers()
{
  try
  {
    int argc;
    char* argv[1];
    Ice::CommunicatorHolder ich(argc, argv);

    auto base = ich->stringToProxy(kProxy_);
    auto gamestate = Ice::checkedCast<Game::GameStatePrx>(base);
    if (!gamestate)
    {
      throw std::runtime_error("Invalid proxy");
    }

    players_ = gamestate->GetPlayers();

  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

vector<int> Client::GetScores()
{
  vector<int> scores(players_.size());
  for (int i = 0; i < players_.size(); i++) {
    scores[i] = players_[i].score;
  }
  return scores;
}

std::vector<std::string> Client::GetNames()
{
  vector<std::string> names(players_.size());
  for (int i = 0; i < players_.size(); i++) {
    names[i] = players_[i].name;
  }
  return names;
}

std::vector<std::string> Client::GetLastGuesses()
{
  vector<std::string> guesses(players_.size());
  for (int i = 0; i < players_.size(); i++) {
    guesses[i] = players_[i].lastguess;
  }
  return guesses;
}

std::vector<bool> Client::GetGuessed()
{
  vector<bool> guessed(players_.size());
  for (int i = 0; i < players_.size(); i++) {
    guessed[i] = players_[i].guessed;
  }
  return guessed;
}
