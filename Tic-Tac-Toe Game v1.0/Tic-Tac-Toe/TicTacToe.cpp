#include <iostream>
#include <vector>
#include <string>

#include "TicTacToe.h"

using namespace std;

TicTacToe::TicTacToe() 
	: question("\nWould you like to be the first to begin (Y/N): ")
	, empty(' ')
	, draw('D')
	, no_winner('N')
	, answer(' ')
	, max_pos(9)
	, min_pos(1)
{
	// fill the vector with spaces
	for (int i = 0; i < 9; ++i)
	{
		board.push_back(empty);
	}
}

void TicTacToe::displayInfo()
{
	cout << "\tWelcome to the Tic-Tac-Toe Game!\n";
	cout << "To make your move enter a number (1 - 9), that corresponds to the desired board position.\n";

	cout << "7 | 8 | 9\n";
	cout << "---------\n";
	cout << "4 | 5 | 6\n";
	cout << "---------\n";
	cout << "1 | 2 | 3\n\n";
}

void TicTacToe::displayBoard()
{
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << endl << endl;
}

void TicTacToe::Answer()
{
	do
	{
		cout << this->question;
		cin >> this->answer;

		// transform the input to lower case
		answer = towlower(answer);

	} while (answer != 'y' && answer != 'n');
}

char TicTacToe::humanSign(const char X, const char O)
{
	if (this->answer == 'y')
	{
		return X;
	}
	else
	{
		return O;
	}
}

char TicTacToe::computerSign(const char X, const char O)
{
	char getHumanSign = humanSign(X, O);

	if (getHumanSign == X)
	{
		return O;
	}
	else
	{
		return X;
	}
}

bool TicTacToe::isLegalMove(int move)
{
	return (board[move - 1] == empty);
}

char TicTacToe::winner()
{
	const int MAX_ROWS = 8;
	//all possible winning pairs
	const int WINNING_PAIRS[MAX_ROWS][3] = { {0, 1, 2},
	                                         {3, 4, 5}, 
									         {6, 7, 8},
									         {0, 3, 6},
								  	         {1, 4, 7},
								       	     {2, 5, 8},
									         {2, 4, 6},
									         {0, 4, 8}
	                                       };

	// check for 3 equal values
	for (int row = 0; row < MAX_ROWS; ++row)
	{
		if ( (board[WINNING_PAIRS[row][0]] != empty) &&
			 (board[WINNING_PAIRS[row][0]] == board[WINNING_PAIRS[row][1]]) &&
			 (board[WINNING_PAIRS[row][1]] == board[WINNING_PAIRS[row][2]]) )
		{
			return board[WINNING_PAIRS[row][0]];
		}
	}

	// return if the game is draw
	if (count(board.begin(), board.end(), empty) == 0)
	{
		return draw;
	}

	return no_winner;
}

void TicTacToe::humanMove(const char X, const char O)
{
	int move;

	do
	{
		cout << "Choose a position: ";
		cin >> move;

		if (!cin)
		{
			cerr << "\nWrong input !\n";
			cin.clear();
			cin.ignore();
		}

	} while (move > max_pos || move < min_pos || !isLegalMove(move));

	board[move - 1] = humanSign(X, O);
}

char TicTacToe::computerMove(const char X, const char O)
{
	char human    = humanSign(X, O);
	char computer = computerSign(X, O);

	// check if computer can win on the next move and do it
	for (int pos = 0; pos < board.size(); ++pos)
	{
		if (isLegalMove(pos + 1))
		{
			board[pos] = computer;
			if (winner() == computer)
			{
				board[pos] = computer;
				return computer;
			}
			else
			{
				// if computer cannot win on the next move, leave the position empty
				board[pos] = empty;
			}
		}
	}

	// check if human can win on next move and block it
	for (int pos = 0; pos < board.size(); ++pos)
	{
		if (isLegalMove(pos + 1))
		{
			board[pos] = human;
			if (winner() == human)
			{
				board[pos] = computer;
				return computer;
			}
			else
			{
				board[pos] = empty;
			}
		}
	}

	// if the previous moves were unsuccessfull, try the best in oreder
	const int REMAINING_POS[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};

	for (int i = 0; i < board.size(); ++i)
	{
		int pos = REMAINING_POS[i];

		if (isLegalMove(pos + 1))
		{
			board[pos] = computer;
			return computer;
		}
	}
}

void TicTacToe::displayWinner(const char X, const char O)
{
	char human    = humanSign(X, O);
	char computer = computerSign(X, O);

	if (human == winner())
	{
		cout << "\nYou've won ! :) " << endl;
	}
	else if (computer == winner())
	{
		cout << "You've lost ! :( " << endl;
	}
	else
	{
		cout << "The game is DRAW !" << endl;
	}
}

bool TicTacToe::isBoardFull()
{
	if (count(board.begin(), board.end(), empty) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}