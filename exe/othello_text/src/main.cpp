/*
 * INCLUDES
 */

#include <iostream>
#include <string>
#include "othello.h"


/*
 * DEFINES
 */

#define PLAYER_HUMAN	0
#define PLAYER_COMPUTER	1


/*
 * PROCESS LINE
 */

bool processLine(const std::string &line)
{
	return true;
}


/*
 * MAIN
 */

int main(int argc, char *argv[])
{
	// Init board
	Othello othello;
	othello.reset();

	// Folders
	std::string savegameDir = "../data/";
	std::string enginesDir = "../bin/";

	// Answer
	std::string answer;
	std::string name;

	// Time
	struct timespec time0, time1;
	double timeDelta;

	// Players
	int playerWhite = PLAYER_HUMAN;
	int playerBlack = PLAYER_HUMAN;

	// Main loop
	while (1)
	{
		// Print board
		othello.printBigColor();
		std::cout << std::endl;

		// Check if computer has to move
		if ((othello.getTurn() == OTHELLO_WHITE &&
			 playerWhite == PLAYER_COMPUTER) ||
			(othello.getTurn() == OTHELLO_BLACK &&
			 playerBlack == PLAYER_COMPUTER))
		{
			if (!othello.engineMove())
			{
				std::cout << "Invalid engine move. Skiping turn";
				std::cout << std::endl;
				othello.skip();
			}

			continue;
		}

		// Ask for new move
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
		else if (answer == "eng_load")
		{
			std::cout << "Engine name> ";
			std::getline(std::cin, name);
			if (!othello.engineLoad((enginesDir + name + ".eng").c_str()))
				std::cout << "Error loading engine" << std::endl;
			continue;
		}
		else if (answer == "eng_move")
		{
			if (!othello.engineMove())
			{
				std::cout << "Invalid engine move";
				std::cout << std::endl;
			}
			continue;
		}
		else if (answer == "eng_name")
		{
			const char *name = othello.engineGetName();
			if (name == NULL)
				std::cout << "Error getting engine name" << std::endl;
			else
				std::cout << "Current engine name: " << name << std::endl;
			continue;
		}
		else if (answer == "eng_prop")
		{
			// TODO
			continue;
		}
		else if (answer == "eng_white")
		{
			playerWhite = PLAYER_COMPUTER;
			playerBlack = PLAYER_HUMAN;
			std::cout << "Computer plays white";
			continue;
		}
		else if (answer == "eng_black")
		{
			playerWhite = PLAYER_HUMAN;
			playerBlack = PLAYER_COMPUTER;
			std::cout << "Computer plays black";
			continue;
		}
		else if (answer == "eng_none")
		{
			playerWhite = PLAYER_HUMAN;
			playerBlack = PLAYER_HUMAN;
			std::cout << "Computer doesn't play";
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
			std::cout << "  eng_load : Loads an engine" << std::endl;
			std::cout << "  eng_move : The current engine does a move" << std::endl;
			std::cout << "  eng_name : Gets current engine name" << std::endl;
			std::cout << "  eng_prop : Sets a property of the current engine" << std::endl;
			std::cout << "  eng_white: Computer plays with white" << std::endl;
			std::cout << "  eng_black: Computer plays with black" << std::endl;
			std::cout << "  eng_nonw : Computer doesn't play" << std::endl;
			std::cout << "  To introduce a new move, write row and column";
			std::cout << " (for example 4f)" << std::endl;
			continue;
		}

		// Add chip
		clock_gettime(CLOCK_REALTIME, &time0);

		if (!othello.move(answer.c_str()))
			std::cout << "Wrong movement" << std::endl;

		clock_gettime(CLOCK_REALTIME, &time1);
		timeDelta =
			1E3 * (double)(time1.tv_sec - time0.tv_sec) +
			1E-6 * (double)(time1.tv_nsec - time0.tv_nsec);
		std::cout << "Motion time: " << timeDelta << "ms" << std::endl;
	}

	return 0;
}

