#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "world.h"
/*
int main()
{
	bool spusti_hru = true;

	while (spusti_hru)
	{
		spusti_hru = false;

		// create game first with all the members of the game structure
		struct game* game = create_game();

		// after successful creation, play the game
		// game loop is located in the function play_game()
		play_game(game);

		if (game->state == RESTART)
			spusti_hru = true;

		// destroy game at the end
		game = destroy_game(game);
	}
	return 0;
}*/

bool is_equal_game(char* str1, char* str2)
{
	if (str1 == NULL && str2 == NULL)
		return true;

	if (str1 == NULL || str2 == NULL)
		return false;

	for (int i = 0;; i++)
	{
		if (str1[i] >= 'A' && str1[i] <= 'Z')
		{
			if (str1[i] != str2[i] && str1[i] + ('a' - 'A') != str2[i])
			{
				return false;
			}
		}
		else if (str1[i] >= 'a' && str1[i] <= 'z')
		{
			if (str1[i] != str2[i] && str1[i] - ('a' - 'A') != str2[i])
			{
				return false;
			}
		}
		else if (str1[i] != str2[i])
		{
			return false;
		}
		else if (str1[i] == 0 && str2[i] == 0)
		{
			return true;
		}
		else if (str1[i] == 0 || str2[i] == 0)
		{
			return false;
		}
	}
}

void recreate_game(struct game* game)
{
	destroy_parser(game->parser);
	destroy_containers(game->world);
	//free(game->current_room);
	destroy_backpack(game->backpack);

	game->state = PLAYING;
	game->parser = create_parser();
	game->world = create_world();
	game->current_room = game->world->room;
	game->backpack = create_backpack(5);
}

void get_input(char* input)
{
	int i = -1;

	do {
		i++;
		input[i] = (char)getc(stdin);
	} while (input[i] != '\n');

	input[i] = 0;
}


void play_game(struct game* game)
{
	if (game == NULL)
		return;
	char input[INPUT_BUFFER_SIZE + 5];

	while (game->state == PLAYING)
	{
		printf("> ");

		get_input(input);
		struct command* prikaz = parse_input(game->parser, input);

		//if (prikaz == NULL)
		//	printf("*** DEBUG: Rozpoznany prikaz: (null)\n");
		//else
		//	printf("*** DEBUG: Rozpoznany prikaz: %s\n",  prikaz->name);

		execute_command(game, prikaz);

		printf("\n");
	}
}

struct game* create_game()
{
	struct game* game = (struct game*)malloc(sizeof(struct game));
	game->state = PLAYING;
	game->parser = create_parser();
	game->world = create_world();
	game->current_room = game->world->room;
	game->backpack = create_backpack(5);

	return game;
}

struct game* destroy_game(struct game* game)
{
	if (game == NULL)
		return NULL;
	destroy_parser(game->parser);
	destroy_containers(game->world);
	//free(game->current_room);
	destroy_backpack(game->backpack);

	free(game);

	return NULL;
}

void save_history(struct game* game, struct command* command)
{
	char* historia = (char*)malloc(101);
	strcpy(historia, command->name);
	if (command->groups != NULL)
	{
		strcat(historia, " ");
		strcat(historia, command->groups[0]);
	}
	struct container* kontajnerHist = create_container(game->parser->history, TEXT, historia);
	if (game->parser->history == NULL)
		game->parser->history = kontajnerHist;
}

void execute_command(struct game* game, struct command* command)
{

	if (game == NULL)
		return;

	if (command == NULL)
	{
		// nenasiel sa taky prikaz
		printf("Neviem co chces urobit!\n");
		return;
	}
	else if (strcmp(command->name, "KONIEC") == 0)
	{
		// Príkaz ukoncí rozohratú hru. Nastaví príslušný stav hry.
		game->state = GAMEOVER;
	}
	else if (strcmp(command->name, "SEVER") == 0)
	{
		// Presun do miestnosti nachádzajúcej sa na sever od aktuálnej. Zmení referenciu aktuálnej miestnosti.
		if (game->current_room->north != NULL)
		{
			game->current_room = game->current_room->north;
			save_history(game, command);
		}
		else
		{
			printf("Tadial cesta nevedie...\n");
		}
	}
	else if (strcmp(command->name, "JUH") == 0)
	{
		// Presun do miestnosti nachádzajúcej sa na juh od aktuálnej. Zmení referenciu aktuálnej miestnosti.
		if (game->current_room->south != NULL)
		{
			game->current_room = game->current_room->south;
			save_history(game, command);
		}
		else
		{
			printf("Tadial cesta nevedie...\n");
		}
	}
	else if (strcmp(command->name, "VYCHOD") == 0)
	{
		// Presun do miestnosti nachádzajúcej sa na východ od aktuálnej. Zmení referenciu aktuálnej miestnosti.
		if (game->current_room->east != NULL)
		{
			game->current_room = game->current_room->east;
			save_history(game, command);
		}
		else
		{
			printf("Tadial cesta nevedie...\n");
		}
	}
	else if (strcmp(command->name, "ZAPAD") == 0)
	{
		// Presun do miestnosti nachádzajúcej sa na západ od aktuálnej. Zmení referenciu aktuálnej miestnosti.
		if (game->current_room->west != NULL)
		{
			game->current_room = game->current_room->west;
			save_history(game, command);
		}
		else
		{
			printf("Tadial cesta nevedie...\n");
		}
	}
	else if (strcmp(command->name, "ROZHLIADNI SA") == 0)
	{
		// Príkaz vypíše aktuálne informácie o miestnosti, v ktorej sa hrác práve nachádza.
		show_room(game->current_room);
		save_history(game, command);
	}
	else if (strcmp(command->name, "PRIKAZY") == 0)
	{
		// Príkaz vypíše na obrazovku zoznam všetkých príkazov, ktoré hra poskytuje.
		struct container* aktualny_kontajner = game->parser->commands;
		while (aktualny_kontajner != NULL)
		{
			printf("%s\t%s\n", aktualny_kontajner->command->name, aktualny_kontajner->command->description);
			aktualny_kontajner = aktualny_kontajner->next;
		}
	}
	else if (strcmp(command->name, "VERZIA") == 0)
	{
		// Príkaz zobrazí císlo verzie hry, lubovolný sprievodný text a meno a priezvisko autora s kontaktom (e-mailová adresa, webová stránka).
		printf("version 1.0\n");
		printf("Hello.\n");
		printf("Name/Mail: Peter Cibulka,petercibulka@gmail.com\n");
	}
	else if (strcmp(command->name, "RESTART") == 0)
	{
		// Znovu spustí hru od zaciatku. Zmení stav hry na požadovaný.
		game->state = RESTART;
	}
	else if (strcmp(command->name, "O HRE") == 0)
	{
		// Príkaz zobrazí krátky text, ktorý poslúži ako úvod do príbehu. Ako dobrý zaciatok sa javí známy text: Kde bolo tam bolo, ..."
		printf("Pribeh o farebnej krabici v prilis dlhom udoli. Dokazes ju otvorit?\n");
	}
	else if (strcmp(command->name, "VEZMI") == 0)
	{
		// Vloží predmet z miestnosti do batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, co chceš vziat.).
		if (command->groups == NULL)
		{
			printf("Neviem co chces vziat.\n");
		}
		else
		{
			struct item* predmet = get_item_from_room(game->current_room, command->groups[0]);
			if (predmet != NULL)
			{
				if (add_item_to_backpack(game->backpack, predmet))
				{
					delete_item_from_room(game->current_room, predmet);
					printf("Zobral si %s.\n", predmet->name);
					save_history(game, command);
				}
				else
				{
					printf("%s sa neda zodvihnut.\n", predmet->name);
				}
			}
			else
				printf("%s tu nie je.\n", command->groups[0]);
		}
	}
	else if (strcmp(command->name, "POLOZ") == 0)
	{
		// Položí predmet z batohu do miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, co chceš položit.)
		if (command->groups == NULL)
		{
			printf("Neviem co chces polozit.\n");
		}
		else
		{
			struct item* predmet = get_item_from_backpack(game->backpack, command->groups[0]);
			if (predmet != NULL)
			{
				add_item_to_room(game->current_room, predmet);
				delete_item_from_backpack(game->backpack, predmet);
				printf("Polozil si %s.\n", predmet->name);
				save_history(game, command);
			}
			else
				printf("%s nie je v batohu.\n", command->groups[0]);
		}
	}
	else if (strcmp(command->name, "INVENTAR") == 0)
	{
		// Zobrazí obsah hrácovho batohu.
		if (game->backpack == NULL)
		{
			printf("Batoh je prazdny.\n");
		}
		else
		{
			printf("V batohu sa nachadza:\n");
			struct container* kontajner = game->backpack->items;
			while (kontajner != NULL)
			{
				printf("   %s\n", kontajner->item->name);
				kontajner = kontajner->next;
				save_history(game, command);
			}
		}
	}
	else if (strcmp(command->name, "POUZI") == 0)
	{
		// Použije predmet z batohu alebo miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, co chceš použit.).


		if (command->groups == NULL)
			printf("Neviem co chces pouzit.\n");

		else
		{
			struct item* predmet = get_item_from_backpack(game->backpack, command->groups[0]);

			if (predmet == NULL)
				predmet = get_item_from_room(game->current_room, command->groups[0]);

			if (predmet == NULL)
			{
				printf("Neviem co chces pouzit.\n");
			}
			else
			{
				// Farebna krabica;
				// po preskumani ziska novy popis "Krabica z neznameho materialu prirastena ku skale. Ma na sebe dva zamky."; strati EXAMINABLE
				// po pouziti cerveneho kluca (az po preskumani) ziska krabica OPENABLE
				// po otvoreni krabice je uspesny koniec hry

				save_history(game, command);

				if (is_equal_game(predmet->name, (char*)"cerveny kluc"))
				{
					struct item* farebna_krabica = get_item_from_room(game->current_room, "farebna krabica");
					if (farebna_krabica == NULL)
					{
						printf("Nemas co odomknut.\n");
					}
					else
					{
						if (farebna_krabica->properties & EXAMINABLE)
							printf("Nemas co odomknut.\n");
						else
						{
							//delete_item_from_backpack(game->backpack, predmet);
							//destroy_item(predmet);
							farebna_krabica->properties = farebna_krabica->properties | OPENABLE;
							printf("Odomkol si %s.\n", farebna_krabica->name);
						}
					}
				}
				else if (is_equal_game(predmet->name, (char*)"farebna krabica"))
				{
					game->state = SOLVED;
					printf("Gratulujem, nasiel si velke bohatstvo.\n[Uspesne si presiel hru!]");
				}
			}
		}
	}
	else if (strcmp(command->name, "PRESKUMAJ") == 0)
	{
		// Vypíše opis predmetu, ktorý sa musí nachádzat v miestnosti alebo batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný alebo sa nenájde v batohu alebo v miestnosti, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, co chceš preskúmat.).
		if (command->groups == NULL)
		{
			printf("Neviem co chces preskumat.\n");
		}
		else
		{
			struct item* predmet = get_item_from_room(game->current_room, command->groups[0]);
			if (predmet == NULL)
			{
				predmet = get_item_from_backpack(game->backpack, command->groups[0]);
			}

			if (predmet != NULL)
			{
				save_history(game, command);

				if (is_equal_game(predmet->name, (char*)"farebna krabica"))
				{
					printf("Krabicu si ocistil od hrubej vrstvy hliny, pod ktorou sa nachadza cerveny zamok.\n\n");
					predmet->properties = predmet->properties & (unsigned int)(~EXAMINABLE);
				}
				printf("%s\n", predmet->description);
			}
			else
				printf("Neviem co chces preskumat.\n");
		}
	}
	else if (strcmp(command->name, "NAHRAJ") == 0)
	{
		// Príkaz zabezpecí nahratie uloženej pozície hry z disku. Volitelným parametrom je cesta k súboru.

		FILE* f;
		if (command->groups != NULL)
		{
			f = fopen(command->groups[0], "rt");
		}
		else
			f = fopen("hra.txt", "rt");

		char buffer[101];

		recreate_game(game);

		while (fgets(buffer, 100, f) != NULL)
		{
			printf("> %s", buffer);

			struct command* prikaz = parse_input(game->parser, buffer);

			execute_command(game, prikaz);

			printf("\n");
		}
		printf("Hra bola uspesne nahrana.\n");
		fclose(f);
	}
	else if (strcmp(command->name, "ULOZ") == 0)
	{
		FILE* f;
		// Príkaz uloží stav rozohratej hry na disk. Volitelným parametrom je cesta k súboru.
		if (command->groups != NULL)
		{
			f = fopen(command->groups[0], "wt");
		}
		else
			f = fopen("hra.txt", "wt");

		struct container* kontajner = game->parser->history;
		while (kontajner != NULL)
		{
			fprintf(f, "%s\n", kontajner->text);
			kontajner = kontajner->next;
		}
		printf("Hra bola uspesne ulozena.\n");
		fclose(f);
	}
	else
	{
		printf("*** neimplementovany prikaz ***\n");
	}
}
