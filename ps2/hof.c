#include <stdio.h>
#include "hof.h"
#include <string.h>

int load(struct player list[]) 
{

	FILE* f = fopen("score", "r");
	char text[30];
	int score;
	int player = 0;

	if (f == NULL)
		return -1;

	while (fscanf(f, "%s %d", text, &score) != EOF)
	{
		strcpy(list[player].name, text);
		list[player].score = score;
		player++;
	}
	for (int j = 0; j < player - 1; j++)
	{
		for (int k = j + 1; k < player; k++)
		{
			if (list[j].score < list[k].score)
			{
				
				score = list[j].score;
				list[j].score = list[k].score;
				list[k].score = score;

				for (int l = 0; l < 30; l++)
				{
					text[l] = list[j].name[l];
					list[j].name[l] = list[k].name[l];
					list[k].name[l] = text[l];
				}
			}
		}
	}

	fclose(f);
	return player;
}

bool save(const struct player list[], const int size)
{
    int ret;

    FILE* f = fopen(HOF_FILE, "wt");
    if (f == NULL)
        return false;

    for (int i = 0; i < size; i++)
    {
        ret = fprintf(f, "%s %d\n", list[i].name, list[i].score);

        if (ret < 0)
        {
            fclose(f);
            return false;
        }
    }

    fclose(f);
    return true;
}

bool add_player(struct player list[], int* size, const struct player player)
{

	bool zapisany = false;
	char text[30];
	int score;
	int TempScore;
	char TempText[30];
	for (int i = 0; i < *size; i++)
	{
		if (list[i].score <= player.score)
		{
			if (*size < 10)
			{
				for (int l = 0; l < 30; l++) 
				{
					list[*size].name[l] = 0;
				}
				list[*size].score = 0;
				*size = *size + 1;
			}
			strcpy(text, player.name);
			score = player.score;
			for (int j = i; j < *size; j++)
			{
				strncpy(TempText, list[j].name, 30);
				TempScore = list[j].score;
				strcpy(list[j].name, text);
				list[j].score = score;
				score = TempScore;
				strncpy(text, TempText, 30);
			}
				zapisany = true;
				break;
		}
	}
	if (zapisany == false && *size < 10)
	{
		*size = *size + 1;
		list[*size - 1].score = player.score;
		strcpy(list[*size - 1].name, player.name);
		zapisany = true;
	}
	return zapisany;
}
