#ifndef OTHELLO
#define OTHELLO

/*
 * INCLUDES
 */

#include <iostream>
#include <fstream>
#include <string.h>
#include <dlfcn.h>

#ifdef ARCH_x86_64
#include "lut64.h"
#else
#include "lut.h"
#endif


/*
 * DEFINES
 */

#define OTHELLO_EMPTY	0
#define OTHELLO_WHITE	1
#define OTHELLO_BLACK	2

#define OTHELLO_HISTORY_SIZE	64

#define OTHELLO_COLOR_RESET			"\033[0m"
#define OTHELLO_COLOR_TILE_WHITE	"\033[1;37;47m"
#define OTHELLO_COLOR_TEXT_WHITE	"\033[1;37m"
#define OTHELLO_COLOR_TILE_BLACK	"\033[1;37;41m"
#define OTHELLO_COLOR_TEXT_BLACK	"\033[1;31m"


/*
 * TYPES
 */

#ifdef ARCH_x86_64
typedef struct
{
	unsigned long white;
	unsigned long black;
}Othello_board;
#else
typedef struct
{
	unsigned int white[2];
	unsigned int black[2];
}Othello_board;
#endif

typedef struct
{
	void *handle;
	const char *(*getName)();
	bool (*setParam)(const char*, const char*);	// Param name, param value
	bool (*move)(Othello_board, int, char*);	// Board, turn, movement
}Othello_engine;


/*
 * CLASSES
 */

class Othello
{
private:
	Othello_board board;
	int turn;
	Othello_board history[OTHELLO_HISTORY_SIZE];
	Othello_engine engine;

public:
	Othello();
	~Othello();

	void reset();

	void printSmall();
	void printBig();
	void printBigColor();

	bool move(const char *move);
	void undo();
	void skip();
	bool load(const char *name);
	bool save(const char *name);

	bool engineLoad(const char *name);
	const char *engineGetName();
	bool engineSetParam(const char *name, const char *value);
	bool engineMove();

private:
	int getCounter();
	int getWhiteCounter();
	int getBlackCounter();
	void getCounters(int &white, int &black);
	int getColor(int row, int col);
	void setColor(int row, int col, int color);

	bool move(int color, int row, int col);

	void saveBoard(std::ofstream &file, Othello_board *board);
	bool loadBoard(std::ifstream &file, Othello_board *board);
};


/*
 * FUNCTIONS
 */

int  Othello_getWhiteCounter(Othello_board *board);
int  Othello_getBlackCounter(Othello_board *board);
int  Othello_getColor(Othello_board *board, int row, int col);
void Othello_setColor(Othello_board *board, int row, int col, int color);
bool Othello_move(Othello_board *board,	int row, int col, int color);

#endif	/* OTHELLO */
