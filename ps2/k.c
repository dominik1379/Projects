#include <stdlib.h>
#include <stdio.h>
#include "k.h"
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

void add_random_tile(struct game* game) {
    int row, col;
    // find random, but empty tile
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if (rand() % 2 == 0) {
        game->board[row][col] = 'A';
    }
    else {
        game->board[row][col] = 'B';
    }
}
bool is_game_won(const struct game game)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++) //matica ma velkost 4x4
        {
            if (game.board[i][j] == 'K') //prejde celu maticu a zisti ci sa nachadza znak "K"
                return true;
        }
    }
    return false;
}

bool is_move_possible(const struct game game)
{	
	bool uspech = false;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (game.board[i][j] == ' ')
				uspech = true;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (game.board[i][j] == game.board[i][j+1])
				uspech = true;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (game.board[i][j] == game.board[i + 1][j])
				uspech = true;
		}
	}
	return uspech;
}

   bool update(struct game* game, int dy, int dx)
{
	bool uspech = false;
	int body[] = { 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 };
	char znak[] = "ABCDEFGHIJK";
	if (dy == 0 && dx == 1) {

		for (int row = 0; row < 4; row++)
		{
			for (int opakuj = 0; opakuj < 4; opakuj++)
			{
				for (int col = 2; col >= 0; col--)
				{
					if (game->board[row][col + 1] == ' ' && game->board[row][col] != ' ')
					{
						game->board[row][col + 1] = game->board[row][col];
						game->board[row][col] = ' ';
						uspech = true;
					}
				}
			}

			for (int col = 2; col >= 0; col--)
			{
				for (int abc = 0; abc < 12; abc++)
				{
					if (game->board[row][col + 1] == znak[abc] && game->board[row][col] == znak[abc])
					{

						game->board[row][col + 1] = znak[abc + 1];
						game->board[row][col] = ' ';
						game->score = game->score + (body[abc] * 2);
						uspech = true;
					}
				}

			}
			for (int col = 2; col >= 0; col--)
			{
				if (game->board[row][col + 1] == ' ' && game->board[row][col] != ' ')
				{
					game->board[row][col + 1] = game->board[row][col];
					game->board[row][col] = ' ';
					uspech = true;
				}
			}
		}
	}

	else if (dx == -1 && dy == 0)

	{

		for (int row = 0; row < 4; row++)
		{
			for (int opakuj = 0; opakuj < 4; opakuj++)
			{
				for (int col = 1; col < 4; col++)
				{
					if (game->board[row][col - 1] == ' ' && game->board[row][col] != ' ')
					{
						game->board[row][col - 1] = game->board[row][col];
						game->board[row][col] = ' ';
						uspech = true;
					}
				}
			}
			for (int abc = 0; abc < 12; abc++)
			{
				for (int col = 1; col < 4; col++)
				{
					if (game->board[row][col - 1] == znak[abc] && game->board[row][col] == znak[abc])
					{
						game->board[row][col - 1] = znak[abc + 1];
						game->board[row][col] = ' ';
						game->score = game->score + (2 * body[abc]);
						uspech = true;
					}
				}
			}
			for (int col = 1; col < 4; col++)
			{
				if (game->board[row][col - 1] == ' ' && game->board[row][col] != ' ')
				{
					game->board[row][col - 1] = game->board[row][col];
					game->board[row][col] = ' ';
					uspech = true;
				}
			}
		}

	}


	else if (dy == 1 && dx == 0)
	{


		for (int col = 0; col < 4; col++)
		{
			for (int opakuj = 0; opakuj < 4; opakuj++)
			{
				for (int row = 2; row >= 0; row--)
				{
					if (game->board[row + 1][col] == ' ' && game->board[row][col] != ' ')
					{
						game->board[row + 1][col] = game->board[row][col];
						game->board[row][col] = ' ';
						uspech = true;
					}
				}
			}
			for (int abc = 0; abc < 12; abc++)
			{
				for (int row = 2; row >= 0; row--)
				{
					if (game->board[row + 1][col] == znak[abc] && game->board[row][col] == znak[abc])
					{
						game->board[row + 1][col] = znak[abc + 1];
						game->board[row][col] = ' ';
						game->score = game->score + (2 * body[abc]);
						uspech = true;
					}
				}
			}
			for (int row = 2; row >= 0; row--)
			{
				if (game->board[row + 1][col] == ' ' && game->board[row][col] != ' ')
				{
					game->board[row + 1][col] = game->board[row][col];
					game->board[row][col] = ' ';
					uspech = true;
				}
			}
		}

	}

	else if (dy == -1 && dx == 0)
	{


		for (int col = 0; col < 4; col++)
		{
			for (int opakuj = 0; opakuj < 4; opakuj++)
			{
				for (int row = 1; row < 4; row++)
				{
					if (game->board[row - 1][col] == ' ' && game->board[row][col] != ' ')
					{
						game->board[row - 1][col] = game->board[row][col];
						game->board[row][col] = ' ';
						uspech = true;
					}
				}
			}
			for (int abc = 0; abc < 12; abc++)
			{
				for (int row = 1; row < 4; row++)
				{
					if (game->board[row - 1][col] == znak[abc] && game->board[row][col] == znak[abc])
					{
						game->board[row - 1][col] = znak[abc + 1];
						game->board[row][col] = ' ';
						game->score = game->score + (2 * body[abc]);
						uspech = true;
					}
				}
			}
			for (int row = 1; row < 4; row++)
			{
				if (game->board[row - 1][col] == ' ' && game->board[row][col] != ' ')
				{
					game->board[row - 1][col] = game->board[row][col];
					game->board[row][col] = ' ';
					uspech = true;
				}
			}
		}

	}
	return uspech;
}