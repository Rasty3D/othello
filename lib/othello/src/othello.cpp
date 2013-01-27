/*
 * INCLUDES
 */

#include "othello.h"


/*
 * CLASSES
 */

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
	this->board.white[0] = 0;
	this->board.white[1] = 0;
	this->board.black[0] = 0;
	this->board.black[1] = 0;
	this->setColor(3, 3, OTHELLO_WHITE);
	this->setColor(4, 4, OTHELLO_WHITE);
	this->setColor(3, 4, OTHELLO_BLACK);
	this->setColor(4, 3, OTHELLO_BLACK);
	this->history[0] = this->board;
	this->turn = OTHELLO_WHITE;
}

void Othello::printSmall()
{
	// Get counters
	int whiteCounter;
	int blackCounter;

	this->getCounters(whiteCounter, blackCounter);

	// Print header
	std::cout << std::endl;
	std::cout << "    1 2 3 4 5 6 7 8" << std::endl;
	std::cout << "    _ _ _ _ _ _ _ _" << std::endl;

	// Print board
	for (int row = 0; row < 8; row++)
	{
		std::cout << (char)(row + 'A') << "  |";

		for (int col = 0; col < 8; col++)
		{
			switch (this->getColor(row, col))
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
		if (row == 0)
			std::cout << "    White: " << whiteCounter;

		// Print black counter in the second row
		if (row == 1)
			std::cout << "    Black: " << blackCounter;

		// Print turn
		if (row == 2)
		{
			std::cout << "    Next movement: ";
			std::cout << (this->turn == OTHELLO_WHITE ? "white" : "black");
		}

		std::cout << std::endl;
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
	for (int row = 0; row < 16; row++)
	{
		if ((row % 2) == 0)
		{
			std::cout << (char)(row / 2 + 'A') << "  |";

			for (int col = 0; col < 8; col++)
			{
				switch (this->getColor(row / 2, col))
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

			for (int col = 0; col < 8; col++)
			{
				switch (this->getColor(row / 2, col))
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
		if (row == 0)
			std::cout << "    White: " << whiteCounter;

		// Print black counter in the second row
		if (row == 1)
			std::cout << "    Black: " << blackCounter;

		// Print turn
		if (row == 2)
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
	for (int row = 0; row < 16; row++)
	{
		if ((row % 2) == 0)
		{
			std::cout << (char)(row / 2 + 'A') << "  |";

			for (int col = 0; col < 8; col++)
			{
				switch (this->getColor(row / 2, col))
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

			for (int col = 0; col < 8; col++)
			{
				switch (this->getColor(row / 2, col))
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
		if (row == 0)
		{
			std::cout << OTHELLO_COLOR_TEXT_WHITE;
			std::cout << "    White: " << whiteCounter;
			std::cout << OTHELLO_COLOR_RESET;
		}

		// Print black counter in the second row
		if (row == 1)
		{
			std::cout << OTHELLO_COLOR_TEXT_BLACK;
			std::cout << "    Red  : " << blackCounter;
			std::cout << OTHELLO_COLOR_RESET;
		}

		// Print turn
		if (row == 2)
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
	int col = -1;

	// Get row & column
	if (move[0] >= '1' && move[0] <= '8')
		col = move[0] - '1';
	else if (move[0] >= 'a' && move[0] <= 'h')
		row = move[0] - 'a';
	else if (move[0] >= 'A' && move[0] <= 'H')
		row = move[0] - 'A';
	else
		return false;

	// Get row & column
	if (move[1] >= '1' && move[1] <= '8')
		col = move[1] - '1';
	else if (move[1] >= 'a' && move[1] <= 'h')
		row = move[1] - 'a';
	else if (move[1] >= 'A' && move[1] <= 'H')
		row = move[1] - 'A';
	else
		return false;

	// Check variables
	if (row == -1 || col == -1)
		return false;

	// Add chip
	return this->addChip(this->turn, row, col);
}

void Othello::undo()
{
	int counter = this->getCounter() - 5;

	if (counter >= 0)
	{
		// Load history
		this->board = this->history[counter];

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
	Othello_board historyAux[OTHELLO_HISTORY_SIZE];

	for (int i = 0; i < OTHELLO_HISTORY_SIZE; i++)
	{
		if (!this->loadBoard(file, &historyAux[i]))
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
				sizeof(Othello_board) * OTHELLO_HISTORY_SIZE);

			// Save board
			this->board = historyAux[i - 1];

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
		this->saveBoard(file, &this->history[i]);

	// Write board
	this->saveBoard(file, &this->board);

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

const char *Othello::engineGetName()
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
	return
		__builtin_popcount(this->board.white[0]) +
		__builtin_popcount(this->board.white[1]) +
		__builtin_popcount(this->board.black[0]) +
		__builtin_popcount(this->board.black[1]);
}

int Othello::getWhiteCounter()
{
	return
		__builtin_popcount(this->board.white[0]) +
		__builtin_popcount(this->board.white[1]);
}

int Othello::getBlackCounter()
{
	return
		__builtin_popcount(this->board.black[0]) +
		__builtin_popcount(this->board.black[1]);
}

void Othello::getCounters(int &white, int &black)
{
	white =
		__builtin_popcount(this->board.white[0]) +
		__builtin_popcount(this->board.white[1]);
	black =
		__builtin_popcount(this->board.black[0]) +
		__builtin_popcount(this->board.black[1]);
}

int Othello::getColor(int row, int col)
{
	int mask = 1 << col;
	unsigned char *lineWhite = (unsigned char*)&this->board.white[0];
	unsigned char *lineBlack = (unsigned char*)&this->board.black[0];

	if (lineWhite[row] & mask)
		return OTHELLO_WHITE;
	else if (lineBlack[row] & mask)
		return OTHELLO_BLACK;
	else
		return OTHELLO_EMPTY;
}

void Othello::setColor(int row, int col, int color)
{
	unsigned char *line;

	if (color == OTHELLO_WHITE)
		line = (unsigned char*)&this->board.white[0];
	else
		line = (unsigned char*)&this->board.black[0];

	line[row] = line[row] | (1 << col);
}

bool Othello::addChip(int color, int row, int col)
{
		/* Save history */

	int counter = this->getCounter() - 4;
	this->history[counter] = this->board;


		/* Do the move */

	Othello_board newBoard = this->board;

	if (!Othello_move(&newBoard, row, col, color))
		return false;

	this->board = newBoard;


		/* Change turn */

	// Change turn
	if (this->turn == OTHELLO_WHITE)
		this->turn = OTHELLO_BLACK;
	else //if (this->turn == OTHELLO_BLACK)
		this->turn = OTHELLO_WHITE;

	// Return ok
	return true;
}

void Othello::saveBoard(std::ofstream &file, Othello_board *board)
{
	file << " 12345678\n";

	for (int row = 0; row < 8; row++)
	{
		file << (char)(row + 'A');

		for (int col = 0; col < 8; col++)
		{
			switch (this->getColor(row, col))
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

bool Othello::loadBoard(std::ifstream &file, Othello_board *board)
{
	// Read a line
	char line[16];

	// Check first line
	file.getline(line, 16);

	if (strcmp(line, " 12345678") == 0)			// Found a board
	{
		// Read board
		for (int row = 0; row < 8; row++)
		{
			file.getline(line, 16);

			if (line[0] != row + 'A')
				return false;

			for (int col = 0; col < 8; col++)
			{
				switch (line[col + 1])
				{
				case ' ':
					this->setColor(row, col, OTHELLO_EMPTY);
					break;
				case 'X':
					this->setColor(row, col, OTHELLO_WHITE);
					break;
				case 'O':
					this->setColor(row, col, OTHELLO_BLACK);
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


/*
 * FUNCTIONS
 */

bool Othello_move(Othello_board *board,	int row, int col, int color)
{
	unsigned char mask = 1 << col;
	unsigned int *lineColor;
	unsigned int *lineOther;
	unsigned int offset = othello_LUTOffset[(col + row * 8) * 2];
	unsigned int size   = othello_LUTOffset[(col + row * 8) * 2 + 1];
	Othello_LUT *lut = &othello_LUT[offset];
	bool moved = false;
	unsigned int other[2];

	if (color == OTHELLO_WHITE)
	{
		lineColor = &board->white[0];
		lineOther = &board->black[0];
	}
	else
	{
		lineColor = &board->black[0];
		lineOther = &board->white[0];
	}

	// Check if the tile is empty
	if (((unsigned char*)board->white)[row] & mask ||
		((unsigned char*)board->black)[row] & mask)
		return false;

	// Iterate in the positions
	for (unsigned int i = 0; i < size; i++)
	{
		other[0] = ~lut[i].color[0] & lut[i].mask[0];
		other[1] = ~lut[i].color[1] & lut[i].mask[1];

		if (((lineColor[0] & lut[i].color[0]) |
			 (lineOther[0] &        other[0])) == lut[i].mask[0] &&
			((lineColor[1] & lut[i].color[1]) |
			 (lineOther[1] &        other[1])) == lut[i].mask[1])
		{
			lineColor[0] += other[0];
			lineColor[1] += other[1];
			lineOther[0] -= other[0];
			lineOther[1] -= other[1];
			moved = true;
		}
	}

	if (moved)
		((unsigned char*)lineColor)[row] |= mask;

	return moved;
}
