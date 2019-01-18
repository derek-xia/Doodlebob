module Game
{
    interface GameState
    {
        void printString(string s);
		int AddPlayer();
		void IncrementScore(int id);
		int GetScore(int id);
		int GetNumPlayers();
    }
}