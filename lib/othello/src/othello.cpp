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

void Othello::printBigColor()
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
					std::cout << OTHELLO_COLOR_TILE_WHITE;
					std::cout << "   ";
					std::cout << OTHELLO_COLOR_RESET;
					std::cout << "|";
					break;
				case OTHELLO_BLACK:
					std::cout << OTHELLO_COLOR_TILE_BLACK;
					std::cout << "   ";
					std::cout << OTHELLO_COLOR_RESET;
					std::cout << "|";
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
					std::cout << OTHELLO_COLOR_TILE_WHITE;
					std::cout << "___";
					std::cout << OTHELLO_COLOR_RESET;
					std::cout << "|";
					break;
				case OTHELLO_BLACK:
					std::cout << OTHELLO_COLOR_TILE_BLACK;
					std::cout << "___";
					std::cout << OTHELLO_COLOR_RESET;
					std::cout << "|";
					break;
				default:
					std::cout << "???|";
				}
			}
		}

		// Print white counter in the first row
		if (i == 0)
		{
			std::cout << OTHELLO_COLOR_TEXT_WHITE;
			std::cout << "    White: " << whiteCounter;
			std::cout << OTHELLO_COLOR_RESET;
		}

		// Print black counter in the second row
		if (i == 1)
		{
			std::cout << OTHELLO_COLOR_TEXT_BLACK;
			std::cout << "    Red  : " << blackCounter;
			std::cout << OTHELLO_COLOR_RESET;
		}

		// Print turn
		if (i == 2)
		{
			std::cout << "    Next movement: ";
			if (this->turn == OTHELLO_WHITE)
			{
				std::cout << OTHELLO_COLOR_TEXT_WHITE;
				std::cout << "white";
			}
			else
			{
				std::cout << OTHELLO_COLOR_TEXT_BLACK;
				std::cout << "red";
			}
			std::cout << OTHELLO_COLOR_RESET;
		}

		std::cout << std::endl;
	}
}

bool Othello::addChip(const char *move)
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
		return false;

	// Get row & column
	if (move[1] >= '1' && move[1] <= '8')
		column = move[1] - '1';
	else if (move[1] >= 'a' && move[1] <= 'h')
		row = move[1] - 'a';
	else if (move[1] >= 'A' && move[1] <= 'H')
		row = move[1] - 'A';
	else
		return false;

	// Check variables
	if (row == -1 || column == -1)
		return false;

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

bool Othello::addChip(int color, int row, int column)
{
		/* Checkings */

	// Check if tile is empty
	if (this->board[column + row * 8] != OTHELLO_EMPTY)
		return false;


		/* Save history */

	int counter = this->getCounter() - 4;
	memcpy(
		&this->history[counter * OTHELLO_BOARD_SIZE],
		this->board,
		OTHELLO_BOARD_SIZE);


		/* Check 8 directions */

	bool check = false;

	if (this->checkDirection(color, row, column, -1, -1)) check = true;
	if (this->checkDirection(color, row, column, -1,  0)) check = true;
	if (this->checkDirection(color, row, column, -1,  1)) check = true;
	if (this->checkDirection(color, row, column,  0, -1)) check = true;
	if (this->checkDirection(color, row, column,  0,  1)) check = true;
	if (this->checkDirection(color, row, column,  1, -1)) check = true;
	if (this->checkDirection(color, row, column,  1,  0)) check = true;
	if (this->checkDirection(color, row, column,  1,  1)) check = true;

	if (!check)
		return false;


		/* Do last things */

	// Set tile color
	this->board[column + row * 8] = color;

	// Change turn
	if (this->turn == OTHELLO_WHITE)
		this->turn = OTHELLO_BLACK;
	else //if (this->turn == OTHELLO_BLACK)
		this->turn = OTHELLO_WHITE;

	// Return ok
	return true;
}

bool Othello::checkDirection(
	int color,
	int row, int column,
	int directionRow, int directionColumn)
{
	// Write in a vector the tiles of the direction
	unsigned char *tiles[8];
	int rowAux;
	int columnAux;

	tiles[0] = NULL;
	tiles[1] = NULL;
	tiles[2] = NULL;
	tiles[3] = NULL;
	tiles[4] = NULL;
	tiles[5] = NULL;
	tiles[6] = NULL;
	tiles[7] = NULL;

	for (int i = 0; i < 8; i++)
	{
		rowAux    = row    + directionRow    * i;
		columnAux = column + directionColumn * i;

		if (rowAux    < 0 || rowAux    >= 8 ||
			columnAux < 0 || columnAux >= 8)
		{
			if (i <= 1)
				return false;
			break;
		}

		tiles[i] = &this->board[columnAux + rowAux * 8];
	}

	/*
	std::cout << "Direction: " << directionColumn << ", " << directionRow << ": ";
	for (int i = 0; i < 8; i++)
	{
		if (tiles[i] == NULL)
			std::cout << "N";
		else if (*tiles[i] == OTHELLO_EMPTY)
			std::cout << "X";
		else if (*tiles[i] == OTHELLO_WHITE)
			std::cout << "W";
		else if (*tiles[i] == OTHELLO_BLACK)
			std::cout << "B";
	}
	std::cout << std::endl;*/

	// Check next tile
	if (tiles[1] == NULL || *tiles[1] == color || *tiles[1] == OTHELLO_EMPTY)
		return false;

	// Look for the line of different color
	for (int i = 2; i <= 8; i++)
	{
		// Not found a tile with the same color
		if (i == 8)
			return false;

		// Not found a tile with the same color
		if (tiles[i] == NULL)
			return false;

		// Found an empty tile
		if (*tiles[i] == OTHELLO_EMPTY)
			return false;

		// Found one with the same color
		if (*tiles[i] == color)
			break;
	}

	// Change color of the line
	for (int i = 1; i < 8; i++)
	{
		// This shouldn't happen
		if (tiles[i] == NULL)
			return false;

		// Finished
		if (*tiles[i] == color)
			return true;

		// Change tile color
		*tiles[i] = color;
	}

	return false;
}
