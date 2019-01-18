# 2D Game
My project idea is a 2D teamwork-based game similar to the iOS game Spaceteam.
One player will be in mission control and the other players will be flying rockets.
The player in mission control will have to direct each player on what actions to take.
If enough actions are missed by any player, the team loses.
I want it to support local multiplayer gameplay using networking.

## Libraries
**OpenFrameworks**:
I will use OpenFrameworks for the graphics and sound libraries.

~**RakNet**: I will use RakNet to implement the multiplayer functionality. RakNet is a networking engine that makes it easier to use TCP/UDP networks. It offers features that allow for both peer to peer and client-server structured games. It also has functions for discovering other players on the same network.~

~**PocoProject**: Poco could be used to write a server for the game if I want to expand the project. Poco has features for writing servers and SQL database access.~

**Ice**: Ice has better documentation and is easier to use. It has client-server RPC functionality.
I will be using RPC to communicate between the client and the server.

## Gameplay
One of the users will create a waiting room, and then other players on the same LAN will be able to see and join the room.
When all the players have joined, the host will be able to start the game.
Then when the game ends, the users will be put back into the waiting room.

## GUI elements
* Start screen
* Waiting room
* Game (Dashboard including a instructions box and buttons, levers, etc...)
* Win/Lose screens
* Leaderboard for time alive
* Settings (if needed)

## Plan
* 11/11-11/17: Set up client GUI and interactions (make buttons work).
* 11/18-12/1: Write server-side functionality and test it through using the server as a local object. Then start networking code.
 - [ ] Write Slice file based on what RPC calls need to be made and compile it.
 - [ ] Implement and test dummy RPC functions.
 - [ ] Implement logic behind RPC functions.
* 12/2-12/12: Add finishing touches like artwork, music, sounds, progressively harder gameplay, and more complicated interactions.

## Relevent Experience
I've written web applications, which are kind of similar to what I'll be doing for this project. I've also created a game before. That experience might be useful for implementing the actual gameplay.