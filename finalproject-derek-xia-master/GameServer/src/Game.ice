module Game
{
	struct Pair 
	{
		int x;
		int y;
	}
	sequence<Pair> Line;
	sequence<Line> LineVector;

	sequence<int> ColorVector;

	struct GameInfo
	{
		int numplayers;
		int currplayer;
		bool inprogress;
		bool changedturn;
		string word;
		string hint;
		int time;
		int round;
	}

	struct Player
	{
		int score;
		string name;
		string lastguess;
		bool guessed;
	}

	sequence<Player> Players;

    interface GameState
    {
        void printString(string s);
		int AddPlayer(string name);
		void IncrementScore(int id);
		int GetScore(int id);
		int GetNumPlayers();

		GameInfo GetGameInfo();

		LineVector GetLines();
		void DrawLines(LineVector lines);
		ColorVector GetColors();
		void DrawColors(ColorVector colors);

		bool CheckWord(string word, int id);

		Players GetPlayers();
    }
}