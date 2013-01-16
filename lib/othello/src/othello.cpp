#include "othello.h"

Othello::Othello()
{
}

Othello::~Othello()
{
}

void Othello::reset()
{
	memset(board, OTHELLO_EMPTY, 64);
	board[27] = OTHELLO_WHITE;
	board[28] = OTHELLO_BLACK;
	board[35] = OTHELLO_BLACK;
	board[36] = OTHELLO_WHITE;
}

void Othello::printSmall()
{
	char row = 'A';

	std::cout << std::endl;
	std::cout << "    1 2 3 4 5 6 7 8" << std::endl;
	std::cout << "    _ _ _ _ _ _ _ _" << std::endl;

	for (int i = 0; i < 8; i++)
	{
		std::cout << row << "  |";

		for (int j = 0; j < 8; j++)
		{
			switch (board[j + i * 8])
			{
			case OTHELLO_EMPTY:
				std::cout << "_|";
				break;
			case OTHELLO_WHITE:
				std::cout << "X|";
				break;
			case OTHELLO_BLACK:
				std::cout << "O|";
				break;
			default:
				std::cout << "?|";
			}
		}

		std::cout << std::endl;
		row++;
	}
}

void Othello::printBig()
{
	std::cout << std::endl;
	std::cout << "     1   2   3   4   5   6   7   8" << std::endl;
	std::cout << "    ___ ___ ___ ___ ___ ___ ___ ___" << std::endl;

	for (int i = 0; i < 16; i++)
	{
		if ((i % 2) == 0)
		{
			std::cout << (char)(i / 2 + 'A') << "  |";

			for (int j = 0; j < 8; j++)
			{
				switch (board[j + (i / 2) * 8])
				{
				case OTHELLO_EMPTY:
					std::cout << "   |";
					break;
				case OTHELLO_WHITE:
					std::cout << "XXX|";
					break;
				case OTHELLO_BLACK:
					std::cout << "/ \\|";
					break;
				default:
					std::cout << "???|";
				}
			}

			std::cout << std::endl;
		}
		else
		{
			std::cout << "   |";

			for (int j = 0; j < 8; j++)
			{
				switch (board[j + (i / 2) * 8])
				{
				case OTHELLO_EMPTY:
					std::cout << "___|";
					break;
				case OTHELLO_WHITE:
					std::cout << "XXX|";
					break;
				case OTHELLO_BLACK:
					std::cout << "\\_/|";
					break;
				default:
					std::cout << "???|";
				}
			}

			std::cout << std::endl;
		}
	}
}
