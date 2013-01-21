#include "othello.h"

Othello::Othello()
{
	this->reset();

	this->engine.handle   = NULL;
	this->engine.getName  = NULL;
	this->engine.setParam = NULL;
	this->engine.move     = NULL;
}

Othello::~Othello()
{
	if (this->engine.handle != NULL)
		dlclose(this->engine.handle);
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

bool Othello::load(const char *name)
{
	// Open file
	std::ifstream file;
	file.open(name);

	if (!file)
		return false;

	// Read history
	unsigned char historyAux[OTHELLO_BOARD_SIZE * OTHELLO_HISTORY_SIZE];

	for (int i = 0; i < OTHELLO_BOARD_SIZE; i++)
	{
		if (!this->loadBoard(file, &historyAux[i * OTHELLO_BOARD_SIZE]))
		{
			file.close();
			return false;
		}

		if (this->turn != OTHELLO_EMPTY)
		{
			// Save history
			memcpy(
				this->history,
				historyAux,
				OTHELLO_BOARD_SIZE * OTHELLO_HISTORY_SIZE);

			// Save board
			memcpy(
				this->board,
				&historyAux[(i - 1) * OTHELLO_BOARD_SIZE],
				OTHELLO_BOARD_SIZE);

			break;
		}
	}

	// Close file and exit
	file.close();
	return true;
}

bool Othello::save(const char *name)
{
	// Get counter
	int counter = this->getCounter();

	// Open file
	std::ofstream file;
	file.open(name);

	if (!file)
		return false;

	// Write history
	for (int i = 0; i < counter - 4; i++)
		this->saveBoard(file, &this->history[i * OTHELLO_BOARD_SIZE]);

	// Write board
	this->saveBoard(file, this->board);

	// Write turn
	if (this->turn == OTHELLO_WHITE)
		file << "Play white\n";
	else //if (this->turn == OTHELLO_BLACK)
		file << "Play black\n";

	// Close file and exit
	file.close();
	return true;
}

bool Othello::engineLoad(const char *name)
{
	if (this->engine.handle != NULL)
		dlclose(this->engine.handle);

	char *error;

	this->engine.handle = dlopen(name, RTLD_NOW | RTLD_LOCAL);

	if (this->engine.handle == NULL)
	{
		std::cout << "Error opening engine [" << dlerror() << "]" << std::endl;
		return false;
	}

	*(void**)(&this->engine.getName) = dlsym(this->engine.handle, "getName");

	if ((error = dlerror()) != NULL)
	{
		std::cout << "Error loading 'getName' function [" << error << "]" << std::endl;
		dlclose(this->engine.handle);
		this->engine.handle = NULL;
		return false;
	}

	*(void**)(&this->engine.setParam) = dlsym(this->engine.handle, "setParam");

	if ((error = dlerror()) != NULL)
	{
		std::cout << "Error loading 'setParam' function [" << error << "]" << std::endl;
		dlclose(this->engine.handle);
		this->engine.handle = NULL;
		return false;
	}

	*(void**)(&this->engine.move) = dlsym(this->engine.handle, "move");

	if ((error = dlerror()) != NULL)
	{
		std::cout << "Error loading 'move' function [" << error << "]" << std::endl;
		dlclose(this->engine.handle);
		this->engine.handle = NULL;
		return false;
	}

	return true;
}

char *Othello::engineGetName()
{
	// Check engine
	if (this->engine.handle  == NULL ||
		this->engine.getName == NULL)
	{
		std::cout << "The engine is not ready" << std::endl;
		return NULL;
	}

	return (this->engine.getName)();
}

bool Othello::engineSetParam(const char *name, const char *value)
{
	// Check engine
	if (this->engine.handle   == NULL ||
		this->engine.setParam == NULL)
	{
		std::cout << "The engine is not ready" << std::endl;
		return false;
	}

	return (this->engine.setParam)(name, value);
}

bool Othello::engineMove()
{
	// Check engine
	if (this->engine.handle == NULL ||
		this->engine.move   == NULL)
	{
		std::cout << "The engine is not ready" << std::endl;
		return false;
	}

	char move[2];

	if (!(this->engine.move)(this->board, this->turn, move))
		return false;

	// Do move
	return this->addChip(move);
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

void Othello::saveBoard(std::ofstream &file, unsigned char *board)
{
	file << " 12345678\n";

	for (int i = 0; i < 8; i++)
	{
		file << (char)(i + 'A');

		for (int j = 0; j < 8; j++)
		{
			switch (board[j + i * 8])
			{
			case OTHELLO_EMPTY:
				file << " ";
				break;
			case OTHELLO_WHITE:
				file << "X";
				break;
			case OTHELLO_BLACK:
				file << "O";
				break;
			default:
				file << "?";
			}
		}

		file << "\n";
	}
}

bool Othello::loadBoard(std::ifstream &file, unsigned char *board)
{
	// Read a line
	char line[16];

	// Check first line
	file.getline(line, 16);

	if (strcmp(line, " 12345678") == 0)			// Found a board
	{
		// Read board
		for (int i = 0; i < 8; i++)
		{
			file.getline(line, 16);

			if (line[0] != i + 'A')
				return false;

			for (int j = 0; j < 8; j++)
			{
				switch (line[j + 1])
				{
				case ' ':
					board[j + i * 8] = OTHELLO_EMPTY;
					break;
				case 'X':
					board[j + i * 8] = OTHELLO_WHITE;
					break;
				case 'O':
					board[j + i * 8] = OTHELLO_BLACK;
					break;
				default:
					return false;
				}
			}
		}

		this->turn = OTHELLO_EMPTY;
		return true;
	}
	else if (strcmp(line, "Play white") == 0)	// Play white
	{
		this->turn = OTHELLO_WHITE;
		return true;
	}
	else if (strcmp(line, "Play black") == 0)	// Play black
	{
		this->turn = OTHELLO_BLACK;
		return true;
	}
	else
	{
		return false;
	}
}
