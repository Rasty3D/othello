#include "othello.h"

static const char *name = "maxchips";

extern "C" const char *getName()
{
	return name;
}

extern "C" bool setParam(const char *name, const char *value)
{
	// No parameters
	return false;
}

extern "C" bool move(Othello_board board, int turn, char *move)
{
	Othello_board boardAux;
	int bestMoveScore = 0;
	int score;

	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			boardAux = board;

			if (Othello_move(&boardAux, row, col, turn))
			{
				if (turn == OTHELLO_WHITE)
					score = Othello_getWhiteCounter(&boardAux);
				else
					score = Othello_getBlackCounter(&boardAux);

				if (bestMoveScore < score)
				{
					bestMoveScore = score;
					move[0] = row + 'A';
					move[1] = col + '1';
				}
			}
		}
	}

	// Check if we could move
	if (bestMoveScore == 0)
		return false;

	std::cout << move[0] << move[1] << std::endl;

	return true;
}
