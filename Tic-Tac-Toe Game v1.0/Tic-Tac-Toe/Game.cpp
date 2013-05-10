#include <iostream>
#include <vector>
#include <limits>

#include "TicTacToe.h"

using namespace std;

// Game constants
const char X = 'X';
const char O = 'O';

int main()
{
	TicTacToe game;

	game.displayInfo();

	game.Answer();

	while (game.winner() == game.noWinner())
	{
		if (game.getAnswer() == 'y')
		{
			game.displayBoard();
			game.humanMove(X, O);
			if (game.winner() == game.humanSign(X, O)) { break; };
			game.displayBoard();
			game.computerMove(X, O);
		}
		else
		{
			game.computerMove(X, O);
			game.displayBoard();
			if (game.isBoardFull()) { break; };
			if (game.winner() == game.computerSign(X, O)) { break; };
			game.humanMove(X, O);
			game.displayBoard();
		}
	}

	game.displayWinner(X, O);

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

	return EXIT_SUCCESS;
}