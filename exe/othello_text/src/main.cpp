#include <iostream>
#include "othello.h"

int main(int argc, char *argv[])
{
	// Init board
	Othello othello;
	othello.reset();

	// Answer
	char answer[128];
	char name[256];

	// Main loop
	while (1)
	{
		// Print board
		othello.printBigColor();

		// Ask for new move
		std::cout << std::endl;
		std::cout << "Enter command> ";
		std::cin >> answer;

		// Check exit
		if (strcmp(answer, "exit") == 0 ||
			strcmp(answer, "quit") == 0)
		{
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
		else if (strcmp(answer, "load") == 0)
		{
			std::cout << "Insert name> ";
			std::cin >> name;
			if (!othello.load(name))
				std::cout << "Error loading game" << std::endl;
			continue;
		}
		else if (strcmp(answer, "save") == 0)
		{
			std::cout << "Insert name> ";
			std::cin >> name;
			if (!othello.save(name))
				std::cout << "Error saving game" << std::endl;
			continue;
		}
		else if (strcmp(answer, "auto") == 0)
		{
			// TODO
			continue;
		}
		else if (strcmp(answer, "help") == 0)
		{
			std::cout << "Command list:" << std::endl;
			std::cout << "  help: Shows this message" << std::endl;
			std::cout << "  quit: Exits the game" << std::endl;
			std::cout << "  exit: Exist the game" << std::endl;
			std::cout << "  undo: Undo the last movement" << std::endl;
			std::cout << "  skip: Skips color movement" << std::endl;
			std::cout << "  new : Starts a new game" << std::endl;
			std::cout << "  load: Loads a game" << std::endl;
			std::cout << "  save: Saves a game" << std::endl;
			std::cout << "  auto: Does an automatic move" << std::endl;
			std::cout << "  To introduce a new move, write row and column";
			std::cout << " (for example 4f)" << std::endl;
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

