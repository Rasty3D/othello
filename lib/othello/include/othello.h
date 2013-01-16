#include <iostream>
#include <string.h>

#define OTHELLO_EMPTY	0
#define OTHELLO_WHITE	1
#define OTHELLO_BLACK	2

class Othello
{
private:
	unsigned char board[64];

public:
	Othello();
	~Othello();

	void reset();

	void printSmall();
	void printBig();
};
