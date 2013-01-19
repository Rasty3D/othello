#include "othello.h"

Othello::Othello()
{
	this->reset();
}

Othello::~Othello()
{
}

void Othello::reset()
{
	memset(this->board, OTHELLO_EMPTY, OTHELLO_BOARD_SIZE);
	this->board[27] = OTHELLO_WHITE;
	this->board[28] = OTHELLO_BLACK;
	this->board[35] = OTHELLO_BLACK;
	this->board[36] = OTHELLO_WHITE;
	memcpy(this->history, this->board, OTHELLO_BOARD_SIZE);
	this->turn = OTHELLO_WHITE;
}

void Othello::printSmall()
{
	// Get counters
	int whiteCounter;
	int blackCounter;

	this->getCounters(whiteCounter, blackCounter);

	// Init row letter
	char row = 'A';

	// Print header
	std::cout << std::endl;
	std::cout << "    1 2 3 4 5 6 7 8" << std::endl;
	std::cout << "    _ _ _ _ _ _ _ _" << std::endl;

	// Print board
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

		// Print white counter in the first row
		if (i == 0)
			std::cout << "    White: " << whiteCounter;

		// Print black counter in the second row
		if (i == 1)
			std::cout << "    Black: " << blackCounter;

		// Print turn
		if (i == 2)
		{
			std::cout << "    Next movement: ";
			std::cout << (this->turn == OTHELLO_WHITE ? "white" : "black");
		}

		std::cout << std::endl;
		row++;
	}
}

void Othello::printBig()
{
	// Get counters
	int whiteCounter;
	int blackCounter;

	this->getCounters(whiteCounter, blackCounter);

	// Print header
	std::cout << std::endl;
	std::cout << "     1   2   3   4   5   6   7   8" << std::endl;
	std::cout << "    ___ ___ ___ ___ ___ ___ ___ ___" << std::endl;

	// Print board
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
		}

		// Print white counter in the first row
		if (i == 0)
			std::cout << "    White: " << whiteCounter;

		// Print black counter in the second row
		if (i == 1)
			std::cout << "    Black: " << blackCounter;

		// Print turn
		if (i == 2)
		{
			std::cout << "    Next movement: ";
			std::cout << (this->turn == OTHELLO_WHITE ? "white" : "black");
		}

		std::cout << std::endl;
	}
}

int Othello::addChip(const char *move)
{
	// Init row and column
	int row = -1;
	int column = -1;

	// Get row & column
	if (move[0] >= '1' && move[0] <= '8')
		column = move[0] - '1';
	else if (move[0] >= 'a' && move[0] <= 'h')
		row = move[0] - 'a';
	else if (move[0] >= 'A' && move[0] <= 'H')
		row = move[0] - 'A';
	else
		return 0;

	// Get row & column
	if (move[1] >= '1' && move[1] <= '8')
		column = move[1] - '1';
	else if (move[1] >= 'a' && move[1] <= 'h')
		row = move[1] - 'a';
	else if (move[1] >= 'A' && move[1] <= 'H')
		row = move[1] - 'A';
	else
		return 0;

	// Check variables
	if (row == -1 || column == -1)
		return 0;

	// Add chip
	return this->addChip(this->turn, row, column);
}

void Othello::undo()
{
	int counter = this->getCounter() - 5;

	if (counter >= 0)
	{
		// Load history
		memcpy(
			this->board,
			&this->history[counter * OTHELLO_BOARD_SIZE],
			OTHELLO_BOARD_SIZE);

		// Change turn
		if (this->turn == OTHELLO_WHITE)
			this->turn = OTHELLO_BLACK;
		else //if (this->turn == OTHELLO_BLACK)
			this->turn = OTHELLO_WHITE;
	}
}

void Othello::skip()
{
	// Change turn
	if (this->turn == OTHELLO_WHITE)
		this->turn = OTHELLO_BLACK;
	else //if (this->turn == OTHELLO_BLACK)
		this->turn = OTHELLO_WHITE;
}

int Othello::getCounter()
{
	int counter = 0;

	for (int i = 0; i < OTHELLO_BOARD_SIZE; i++)
	{
		if (this->board[i] != OTHELLO_EMPTY)
			counter++;
	}

	return counter;
}

int Othello::getWhiteCounter()
{
	int counter = 0;

	for (int i = 0; i < OTHELLO_BOARD_SIZE; i++)
	{
		if (this->board[i] == OTHELLO_WHITE)
			counter++;
	}

	return counter;
}

int Othello::getBlackCounter()
{
	int counter = 0;

	for (int i = 0; i < OTHELLO_BOARD_SIZE; i++)
	{
		if (this->board[i] == OTHELLO_BLACK)
			counter++;
	}

	return counter;
}

void Othello::getCounters(int &white, int &black)
{
	white = 0;
	black = 0;

	for (int i = 0; i < OTHELLO_BOARD_SIZE; i++)
	{
		if (this->board[i] == OTHELLO_WHITE)
			white++;
		else if (this->board[i] == OTHELLO_BLACK)
			black++;
	}
}

int Othello::addChip(int color, int row, int column)
{
		/* Checkings */

	// Check if tile is empty
	if (this->board[column + row * 8] != OTHELLO_EMPTY)
		return 0;


		/* Check 8 directions */

	int otherColor = (color == OTHELLO_WHITE ? OTHELLO_BLACK : OTHELLO_WHITE);

	// Direction N
	if (row > 1 && this->board[column + (row - 1) * 8] == otherColor)
	{
		for (int i = row - 2; i >= 0; i--)
		{
			if (this->board[column + i * 8] == color)
			{
				for (int j = i + 1; j < row; j++)
					this->board[column + j * 8] = color;

				break;
			}
		}
	}


		/* Do last things */

	// Save history
	int counter = this->getCounter() - 4;
	memcpy(
		&this->history[counter * OTHELLO_BOARD_SIZE],
		this->board,
		OTHELLO_BOARD_SIZE);

	// Set tile color
	this->board[column + row * 8] = color;

	// Change turn
	if (this->turn == OTHELLO_WHITE)
		this->turn = OTHELLO_BLACK;
	else //if (this->turn == OTHELLO_BLACK)
		this->turn = OTHELLO_WHITE;

	// Return ok
	return 1;
}
