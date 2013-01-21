#include <iostream>
#include <fstream>
#include <string.h>
#include <dlfcn.h>

#define OTHELLO_EMPTY	0
#define OTHELLO_WHITE	1
#define OTHELLO_BLACK	2

#define OTHELLO_BOARD_SIZE		64
#define OTHELLO_HISTORY_SIZE	64

#define OTHELLO_COLOR_RESET			"\033[0m"
#define OTHELLO_COLOR_TILE_WHITE	"\033[1;37;47m"
#define OTHELLO_COLOR_TEXT_WHITE	"\033[1;37m"
#define OTHELLO_COLOR_TILE_BLACK	"\033[1;37;41m"
#define OTHELLO_COLOR_TEXT_BLACK	"\033[1;31m"

typedef struct
{
	void *handle;
	char *(*getName)();
	bool (*setParam)(const char*, const char*);		// Param name, param value
	bool (*move)(const unsigned char*, int, char*);	// Board, turn, movement
}Othello_engine;

class Othello
{
private:
	unsigned char board[OTHELLO_BOARD_SIZE];
	int turn;
	unsigned char history[OTHELLO_BOARD_SIZE * OTHELLO_HISTORY_SIZE];
	Othello_engine engine;

public:
	Othello();
	~Othello();

	void reset();

	void printSmall();
	void printBig();
	void printBigColor();

	bool addChip(const char *move);
	void undo();
	void skip();
	bool load(const char *name);
	bool save(const char *name);

	bool engineLoad(const char *name);
	char *engineGetName();
	bool engineSetParam(const char *name, const char *value);
	bool engineMove();

private:
	int getCounter();
	int getWhiteCounter();
	int getBlackCounter();
	void getCounters(int &white, int &black);

	bool addChip(int color, int row, int column);

	bool checkDirection(
		int color,
		int row, int column,
		int directionRow, int directionColumn);

	void saveBoard(std::ofstream &file, unsigned char *board);
	bool loadBoard(std::ifstream &file, unsigned char *board);
};
