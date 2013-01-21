#include <iostream>
#include <string>
#include "othello.h"

int main(int argc, char *argv[])
{
	// Init board
	Othello othello;
	othello.reset();

	// Savegame folder
	std::string rootDir = ROOT_DIR;
	std::string savegameDir = rootDir + "/data/";

	// Answer
	std::string answer;
	std::string name;

	// Main loop
	while (1)
	{
		// Print board
		othello.printBigColor();

		// Ask for new move
		std::cout << std::endl;
		std::cout << "Enter command> ";
		std::getline(std::cin, answer);

		// Check exit
		if (answer == "exit" || answer == "quit")
		{
			break;
		}
		else if (answer == "undo")
		{
			othello.undo();
			continue;
		}
		else if (answer == "skip")
		{
			othello.skip();
			continue;
		}
		else if (answer == "new")
		{
			othello.reset();
			continue;
		}
		else if (answer == "load")
		{
			std::cout << "Insert name> ";
			std::getline(std::cin, name);
			if (!othello.load((savegameDir + name).c_str()))
				std::cout << "Error loading game" << std::endl;
			continue;
		}
		else if (answer == "save")
		{
			std::cout << "Insert name> ";
			std::getline(std::cin, name);
			if (!othello.save((savegameDir + name).c_str()))
				std::cout << "Error saving game" << std::endl;
			continue;
		}
		else if (answer == "auto")
		{
			// TODO
			continue;
		}
		else if (answer == "help")
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

		// Add chip
		if (!othello.addChip(answer.c_str()))
			std::cout << "Wrong movement" << std::endl;

	}

	return 0;
}

