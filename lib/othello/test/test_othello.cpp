#include <iostream>
#include "othello.h"

int main(int argc, char *argv[])
{
	Othello othello;

	othello.reset();
	othello.printSmall();
	othello.printBig();

	return 0;
}

