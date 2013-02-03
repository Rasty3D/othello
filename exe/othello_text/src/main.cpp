/*
 * INCLUDES
 */

#include <iostream>
#include <string>
#include <dirent.h>
#include "othello.h"


/*
 * DEFINES
 */

#define PLAYER_HUMAN	0
#define PLAYER_COMPUTER	1

#define PATH_SAVEGAME		"../data/"
#define PATH_ENGINES		"../bin/"


/*
 * PROCESS LINE
 */

bool tokenize(char *line, int &argc, char **argv)
{
	argc = 0;			// Number of tokens
	int situation = 0;	// 0: unknown, 1: separator, 2: string, 3: word
	int lineSize = strlen(line);

	// Iterate in the line to separate in tokens
	// "" and '' mark strings
	for (int i = 0; i < lineSize; i++)
	{
		switch (situation)
		{
		case 1:
			if (line[i] == ' '  || line[i] == '\t' ||
				line[i] == '\n' || line[i] == '\r')
			{
				line[i] = '\0';
				situation = 1;
			}
			else if (line[i] == '\'' || line[i] == '\"')
			{
				line[i] = '\0';
				argv[argc] = &line[i + 1];
				situation = 2;
			}
			else
			{
				argv[argc] = &line[i];
				situation = 3;
			}
			break;
		case 2:
			if (line[i] == '\'' || line[i] == '\"')
			{
				line[i] = '\0';
				argc++;
				situation = 1;
			}
			break;
		case 3:
			if (line[i] == ' '  || line[i] == '\t' ||
				line[i] == '\n' || line[i] == '\r')
			{
				line[i] = '\0';
				argc++;
				situation = 1;
			}
			else if (line[i] == '\'' || line[i] == '\"')
			{
				return false;
			}
			break;
		default:
			if (line[i] == ' '  || line[i] == '\t' ||
				line[i] == '\n' || line[i] == '\r')
			{
				line[i] = '\0';
				situation = 1;
			}
			else if (line[i] == '\'' || line[i] == '\"')
			{
				line[i] = '\0';
				argv[argc] = &line[i + 1];
				situation = 2;
			}
			else
			{
				argv[argc] = &line[i];
				situation = 3;
			}
			break;
		}
	}

	if (situation == 2)
		return false;
	else if (situation == 3)
		argc++;

	return true;
}

bool processLine(
	const std::string &answer, Othello &othello,
	int &playerWhite, int &playerBlack)
{
	if (answer.size() <= 0)	// Nothing to do
		return true;


		/* Separate line in tokens */

	int argc = 0;
	char **argv = new char*[answer.size()];
	char *line = new char[answer.size() + 1];
	strcpy(line, answer.c_str());
	line[answer.size()] = '\0';

	if (!tokenize(line, argc, argv))
	{
		std::cout << "Wrong formated command" << std::endl;
		return true;
	}

	if (argc == 0)
		return true;

	// Print tokens
	/*
	std::cout << "Tokens [" << argc << "]:" << std::endl;
	for (int i = 0; i < argc; i++)
		std::cout << "  " << i << " [" << argv[i] << "]" << std::endl;*/


		/* Variables */

	// Folders
	std::string savegameDir = PATH_SAVEGAME;
	std::string enginesDir = PATH_ENGINES;

	// Time
	struct timespec time0, time1;
	double timeDelta;


		/* Process command */

	// Check exit
	if (strcmp(argv[0], "exit") == 0 || strcmp(argv[0], "quit") == 0)
	{
		delete [] line;
		delete [] argv;
		return false;
	}
	else if (strcmp(argv[0], "undo") == 0)
	{
		othello.undo();
	}
	else if (strcmp(argv[0], "skip") == 0)
	{
		othello.skip();
	}
	else if (strcmp(argv[0], "new") == 0)
	{
		othello.reset();
	}
	else if (strcmp(argv[0], "load") == 0)
	{
		if (argc < 2)
		{
			std::cout << "Please, introduce the game name:" << std::endl;
			std::cout << "  load [game name]" << std::endl;
		}
		else
		{
			if (!othello.load((savegameDir + argv[1]).c_str()))
				std::cout << "Error loading game" << std::endl;
		}
	}
	else if (strcmp(argv[0], "save") == 0)
	{
		if (argc < 2)
		{
			std::cout << "Please, introduce the game name:" << std::endl;
			std::cout << "  save [game name]" << std::endl;
		}
		else
		{
			if (!othello.save((savegameDir + argv[1]).c_str()))
				std::cout << "Error saving game" << std::endl;
		}
	}
	else if (strcmp(argv[0], "eng_list") == 0)
	{
		DIR *dir = opendir(PATH_ENGINES);
		struct dirent *ent;
		int nameLen;

		if (dir)
		{
			std::cout << "List of engines:" << std::endl;

			while ((ent = readdir(dir)) != NULL)
			{
				if (ent->d_type == DT_REG)
				{
					nameLen = strlen(ent->d_name);

					if (nameLen > 5 &&
						ent->d_name[nameLen - 4] == '.' &&
						ent->d_name[nameLen - 3] == 'e' &&
						ent->d_name[nameLen - 2] == 'n' &&
						ent->d_name[nameLen - 1] == 'g')
					{
						ent->d_name[nameLen - 4] = '\0';
						std::cout << "  " << ent->d_name << std::endl;
					}
				}
			}

			closedir(dir);
		}
		else
		{
			std::cout << "Error reading the engines folder" << std::endl;
		}
	}
	else if (strcmp(argv[0], "eng_load") == 0)
	{
		if (argc < 2)
		{
			std::cout << "Please, introduce the engine name:" << std::endl;
			std::cout << "  eng_load [engine name]" << std::endl;
		}
		else
		{
			if (!othello.engineLoad((enginesDir + argv[1] + ".eng").c_str()))
				std::cout << "Error loading engine" << std::endl;
			else
				std::cout << "Engine ready" << std::endl;
		}
	}
	else if (strcmp(argv[0], "eng_move") == 0)
	{
		if (!othello.engineReady())
			std::cout << "Engine not ready" << std::endl;
		else if (!othello.engineMove())
			std::cout << "Invalid engine move" << std::endl;
	}
	else if (strcmp(argv[0], "eng_name") == 0)
	{
		const char *name = othello.engineGetName();

		if (name == NULL)
			std::cout << "Error getting engine name" << std::endl;
		else
			std::cout << "Current engine name: " << name << std::endl;
	}
	else if (strcmp(argv[0], "eng_param") == 0)
	{
		if (!othello.engineReady())
		{
			playerWhite = PLAYER_HUMAN;
			playerBlack = PLAYER_HUMAN;
			std::cout << "Engine not ready" << std::endl;
		}
		else if (argc < 3)
		{
			std::cout << "Please, introduce the parameter name and value:" << std::endl;
			std::cout << "  eng_param [name] [value]" << std::endl;
		}
	}
	else if (strcmp(argv[0], "eng_white") == 0)
	{
		if (!othello.engineReady())
		{
			playerWhite = PLAYER_HUMAN;
			playerBlack = PLAYER_HUMAN;
			std::cout << "Engine not ready" << std::endl;
		}
		else
		{
			playerWhite = PLAYER_COMPUTER;
			playerBlack = PLAYER_HUMAN;
			std::cout << "Computer plays white" << std::endl;
		}
	}
	else if (strcmp(argv[0], "eng_black") == 0)
	{
		if (!othello.engineReady())
		{
			playerWhite = PLAYER_HUMAN;
			playerBlack = PLAYER_HUMAN;
			std::cout << "Engine not ready" << std::endl;
		}
		else
		{
			playerWhite = PLAYER_HUMAN;
			playerBlack = PLAYER_COMPUTER;
			std::cout << "Computer plays black" << std::endl;
		}
	}
	else if (strcmp(argv[0], "eng_none") == 0)
	{
		playerWhite = PLAYER_HUMAN;
		playerBlack = PLAYER_HUMAN;
		std::cout << "Computer doesn't play" << std::endl;
	}
	else if (strcmp(argv[0], "help") == 0)
	{
		std::cout << std::endl;
		std::cout << "To introduce a new move, write row and column (for example 4f)" << std::endl;
		std::cout << std::endl;
		std::cout << "Command list:" << std::endl;
		std::cout << "  help                     Shows this message" << std::endl;
		std::cout << "  quit                     Exits the game" << std::endl;
		std::cout << "  exit                     Exist the game" << std::endl;
		std::cout << "  undo                     Undo the last movement" << std::endl;
		std::cout << "  skip                     Skips color movement" << std::endl;
		std::cout << "  new                      Starts a new game" << std::endl;
		std::cout << "  load [game name]         Loads a game" << std::endl;
		std::cout << "  save [game name]         Saves a game" << std::endl;
		std::cout << "  eng_list                 List the available engines" << std::endl;
		std::cout << "  eng_load [engine name]   Loads an engine" << std::endl;
		std::cout << "  eng_move                 The current engine does a move" << std::endl;
		std::cout << "  eng_name                 Gets current engine name" << std::endl;
		std::cout << "  eng_param [name] [value] Sets a parameter of the current engine" << std::endl;
		std::cout << "  eng_white                Computer plays with white" << std::endl;
		std::cout << "  eng_black                Computer plays with black" << std::endl;
		std::cout << "  eng_none                 Computer doesn't play" << std::endl;
	}
	else
	{
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


		/* Destroy things and exit */

	// Delete tokenized line
	delete [] line;
	delete [] argv;

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

	// Answer
	std::string answer;

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

		if (!processLine(answer, othello, playerWhite, playerBlack))
			break;
	}

	return 0;
}

