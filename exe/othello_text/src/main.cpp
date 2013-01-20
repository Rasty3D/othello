#include <iostream>
#include "othello.h"

int main(int argc, char *argv[])
{
	// Init board
	Othello othello;
	othello.reset();

	// Move
	char answer[128];
	char move[3];

	// Main loop
	while (1)
	{
		// Print board
		othello.printBigColor();

		// Ask for new move
		std::cout << std::endl;
		std::cout << "Next movement: ";
		std::cin >> answer;

		// Check exit
		if (strcmp(answer, "exit") == 0 ||
			strcmp(answer, "quit") == 0)
		{
			// Prompt to exit: TODO
			break;
		}
		else if (strcmp(answer, "undo") == 0)
		{
			othello.undo();
			continue;
		}
		else if (strcmp(answer, "skip") == 0)
		{
			othello.skip();
			continue;
		}
		else if (strcmp(answer, "new") == 0)
		{
			othello.reset();
			continue;
		}
		else if (strcmp(answer, "help") == 0)
		{
			// Print help: TODO
			continue;
		}

		// Check other options (save, load, help, etc)
		// TODO

		// Add chip
		if (!othello.addChip(answer))
			std::cout << "Wrong movement" << std::endl;

	}

	return 0;
}

