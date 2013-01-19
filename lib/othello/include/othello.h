#include <iostream>
#include <string.h>

#define OTHELLO_EMPTY	0
#define OTHELLO_WHITE	1
#define OTHELLO_BLACK	2

#define OTHELLO_BOARD_SIZE		64
#define OTHELLO_HISTORY_SIZE	60

class Othello
{
private:
	unsigned char board[OTHELLO_BOARD_SIZE];
	int turn;
	unsigned char history[OTHELLO_BOARD_SIZE * OTHELLO_HISTORY_SIZE];

public:
	Othello();
	~Othello();

	void reset();

	void printSmall();
	void printBig();

	int addChip(const char *move);
	void undo();
	void skip();

private:
	int getCounter();
	int getWhiteCounter();
	int getBlackCounter();
	void getCounters(int &white, int &black);

	int addChip(int color, int row, int column);
};
