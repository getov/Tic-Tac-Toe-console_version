#pragma once

class TicTacToe
{
	private:
		std::vector<char> board;
		std::string question;

		char empty;
		char draw;
		char no_winner;
		char answer;

		int max_pos;
		int min_pos;

	public:
		TicTacToe();

		void displayInfo();
		void displayBoard();

		// Decide which turn to play the game: first or second
		void Answer();

		// decide what to play with: 'X' or 'O'
		char humanSign(const char X, const char O);
		char computerSign(const char X, const char O);

		bool isLegalMove(int move);

		// find out who is the winner
		char winner();

		void humanMove(const char X, const char O);
		char computerMove(const char X, const char O);

		void displayWinner(const char X, const char O);

		// checks if all positions are occupied
		bool isBoardFull();

		char noWinner()
		{
			return this->no_winner;
		}

		char getAnswer()
		{
			return this->answer;
		}
};