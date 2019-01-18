#include <Ice/Ice.h>
#include "Game.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;
using namespace Game;

int
main(int argc, char* argv[])
{
  try
  {
    Ice::CommunicatorHolder ich(argc, argv);
    auto base = ich->stringToProxy("GameServer:default -p 10000");
    auto gameState = Ice::checkedCast<GameStatePrx>(base);
    if (!gameState)
    {
      throw std::runtime_error("Invalid proxy");
    }
    string message;
    int id = gameState->AddPlayer(); // Adds itself to the server
    while (true) {
      cin >> message;
      gameState->IncrementScore(id);
      gameState->GetScore(id);
    }
    
  }
  catch (const std::exception& e)
  {
    cerr << e.what() << endl;
    return 1;
  }
  return 0;
}