#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include <string.h>

char* vytvor_string_parser(const char* retazec)
{
	char* novy_retazec = (char*)malloc(strlen(retazec) + 1);
	strcpy(novy_retazec, retazec);
	return novy_retazec;
}

void vytvor_prikazy(struct parser* parser)
{
	char* name;
	char* description;
	char* pattern;
	size_t nmatch;
	struct command* command;

	size_t nmatch_prikaz = 0;
	size_t nmatch_prikaz_s_1_parametrom = 3;

	name = vytvor_string_parser("KONIEC");
	description = vytvor_string_parser("Ukoncenie hry.");
	pattern = vytvor_string_parser("^\\s*(KONIEC|QUIT|EXIT)\\s*$");
	nmatch = nmatch_prikaz;
	command = create_command(name, description, pattern, nmatch);
	parser->commands = create_container(NULL, COMMAND, command);

	name = vytvor_string_parser("SEVER");
	description = vytvor_string_parser("Presun do miestnosti nachadzajucej sa na sever od aktualnej.");
	pattern = vytvor_string_parser("^\\s*(SEVER|S)\\s*$");
	nmatch = nmatch_prikaz;
	command = create_command(name, description, pattern, nmatch);
	create_container(parser->commands, COMMAND, command);

	name = vytvor_string_parser("JUH");
	description = vytvor_string_parser("Presun do miestnosti nachadzajucej sa na juh od aktualnej.");
	pattern = vytvor_string_parser("^\\s*(JUH|J)\\s*$");
	nmatch = nmatch_prikaz;
	command = create_command(name, description, pattern, nmatch);
	create_container(parser->commands, COMMAND, command);

	name = vytvor_string_parser("VYCHOD");
	description = vytvor_string_parser("Presun do miestnosti nachadzajucej sa na vychod od aktualnej.");
	pattern = vytvor_string_parser("^\\s*(VYCHOD|V)\\s*$");
	nmatch = nmatch_prikaz;
	command = create_command(name, description, pattern, nmatch);
	create_container(parser->commands, COMMAND, command);

	name = vytvor_string_parser("ZAPAD");
	description = vytvor_string_parser("Presun do miestnosti nachadzajucej sa na zapad od aktualnej.");
	pattern = vytvor_string_parser("^\\s*(ZAPAD|Z)\\s*$");
	nmatch = nmatch_prikaz;
	command = create_command(name, description, pattern, nmatch);
	create_container(parser->commands, COMMAND, command);

	name = vytvor_string_parser("ROZHLIADNI SA");
	description = vytvor_string_parser("Prikaz vypise aktualne informacie o miestnosti, v ktorej sa hrac prave nachadza.");
	pattern = vytvor_string_parser("^\\s*(ROZHLIADNI\\s*SA)\\s*$");
	nmatch = nmatch_prikaz;
	command = create_command(name, description, pattern, nmatch);
	create_container(parser->commands, COMMAND, command);

	name = vytvor_string_parser("PRIKAZY");
	description = vytvor_string_parser("Zoznam prikazov.");
	pattern = vytvor_string_parser("^\\s*(PRIKAZY|HELP|POMOC)\\s*$");
	nmatch = nmatch_prikaz;
	command = create_command(name, description, pattern, nmatch);
	create_container(parser->commands, COMMAND, command);

	name = vytvor_string_parser("VERZIA");
	description = vytvor_string_parser("Informacie o verzii hry a o autorovi.");
	pattern = vytvor_string_parser("^\\s*(VERZIA)\\s*$");
	nmatch = nmatch_prikaz;
	command = create_command(name, description, pattern, nmatch);
	create_container(parser->commands, COMMAND, command);

	name = vytvor_string_parser("RESTART");
	description = vytvor_string_parser("Znovu spusti hru od zaciatku.");
	pattern = vytvor_string_parser("^\\s*(RESTART)\\s*$");
	nmatch = nmatch_prikaz;
	command = create_command(name, description, pattern, nmatch);
	create_container(parser->commands, COMMAND, command);

	name = vytvor_string_parser("O HRE");
	description = vytvor_string_parser("Uvod do pribehu.");
	pattern = vytvor_string_parser("^\\s*(O\\s*HRE|ABOUT)\\s*$");
	nmatch = nmatch_prikaz;
	command = create_command(name, description, pattern, nmatch);
	create_container(parser->commands, COMMAND, command);

	name = vytvor_string_parser("VEZMI");
	description = vytvor_string_parser("Vlozi predmet z miestnosti do batohu. Prikaz ma jeden povinny parameter, ktorym je nazov predmetu.");
	pattern = vytvor_string_parser("^\\s*(VEZMI)\\s*(.*)");
	nmatch = nmatch_prikaz_s_1_parametrom;
	command = create_command(name, description, pattern, nmatch);
	create_container(parser->commands, COMMAND, command);

	name = vytvor_string_parser("POLOZ");
	description = vytvor_string_parser("Polozi predmet z batohu do miestnosti. Prikaz ma jeden povinny parameter, ktorym je nazov predmetu.");
	pattern = vytvor_string_parser("^\\s*(POLOZ)\\s*(.*)");
	nmatch = nmatch_prikaz_s_1_parametrom;
	command = create_command(name, description, pattern, nmatch);
	create_container(parser->commands, COMMAND, command);

	name = vytvor_string_parser("INVENTAR");
	description = vytvor_string_parser("Zobrazi obsah batohu.");
	pattern = vytvor_string_parser("^\\s*(INVENTAR|I)\\s*$");
	nmatch = nmatch_prikaz;
	command = create_command(name, description, pattern, nmatch);
	create_container(parser->commands, COMMAND, command);

	name = vytvor_string_parser("POUZI");
	description = vytvor_string_parser("Pouzije predmet z batohu alebo miestnosti. Prikaz ma jeden povinny parameter, ktorym je nazov predmetu.");
	pattern = vytvor_string_parser("^\\s*(POUZI)\\s*(.*)");
	nmatch = nmatch_prikaz_s_1_parametrom;
	command = create_command(name, description, pattern, nmatch);
	create_container(parser->commands, COMMAND, command);

	name = vytvor_string_parser("PRESKUMAJ");
	description = vytvor_string_parser("Vypise opis predmetu, ktory sa musi nachadzat v miestnosti alebo batohu. Prikaz ma jeden povinny parameter, ktorym je nazov predmetu.");
	pattern = vytvor_string_parser("^\\s*(PRESKUMAJ)\\s*(.*)");
	nmatch = nmatch_prikaz_s_1_parametrom;
	command = create_command(name, description, pattern, nmatch);
	create_container(parser->commands, COMMAND, command);

	name = vytvor_string_parser("NAHRAJ");
	description = vytvor_string_parser("Prikaz zabezpeci nahratie ulozenej pozicie hry z disku. Volitelnym parametrom je cesta k suboru.");
	pattern = vytvor_string_parser("^\\s*(NAHRAJ|LOAD)\\s*(.*)");
	nmatch = nmatch_prikaz_s_1_parametrom;
	command = create_command(name, description, pattern, nmatch);
	create_container(parser->commands, COMMAND, command);

	name = vytvor_string_parser("ULOZ");
	description = vytvor_string_parser("Prikaz ulozi stav rozohratej hry na disk. Volitelnym parametrom je cesta k suboru.");
	pattern = vytvor_string_parser("^\\s*(ULOZ|SAVE)\\s*(.*)");
	nmatch = nmatch_prikaz_s_1_parametrom;
	command = create_command(name, description, pattern, nmatch);
	create_container(parser->commands, COMMAND, command);
}

struct parser* create_parser()
{
	struct parser* parser = (struct parser*)malloc(sizeof(struct parser));
	parser->history = NULL;
	vytvor_prikazy(parser);
	return parser;
}


struct parser* destroy_parser(struct parser* parser)
{
	if (parser != NULL)
	{
		destroy_containers(parser->history);
		destroy_containers(parser->commands);
		free(parser);
	}
	return NULL;
}

void clear_command_params(struct command* prikaz)
{
	if (prikaz != NULL && prikaz->groups != NULL)
	{
		int i = 0;
		while (prikaz->groups[i] != NULL)
		{
			free(prikaz->groups[i]);
			i++;
		}
		free(prikaz->groups);
		prikaz->groups = NULL;
	}
}

struct command* parse_input(struct parser* parser, char* input)
{
	if (parser == NULL || input == NULL || input[0] == 0)
		return NULL;

	struct container* prikaz_kontajner = parser->commands;
	while (prikaz_kontajner != NULL)
	{
		struct command* cmd = prikaz_kontajner->command;
		size_t nmatch = cmd->nmatch;
		if (nmatch > 10)
			nmatch = 10;
		regmatch_t groups[10];

		int result = regexec(&cmd->preg, input, nmatch, groups, 0);
		if (result != REG_NOMATCH)
		{
			clear_command_params(prikaz_kontajner->command);
			if (groups[2].rm_so > -1)
			{
				int zaciatok = groups[2].rm_so + 1;
				int dlzka = groups[2].rm_eo - groups[2].rm_so - 1;
				char parameter[101];
				if (dlzka <= 0)
					return cmd;
				strncpy(parameter, &input[zaciatok], (size_t)dlzka);
				parameter[dlzka] = 0;

				// odstranim medzery na konci
				int i = dlzka - 1;
				while (parameter[i] == ' ' || parameter[i] == '\t' || parameter[i] == '\r' || parameter[i] == '\n')
				{
					i--;
				}
				parameter[i + 1] = 0;

				size_t pocetArgumentov = 2;
				cmd->groups = (char**)malloc(sizeof(char*) * pocetArgumentov);
				cmd->groups[0] = vytvor_string_parser(parameter);
				cmd->groups[1] = NULL;


			}

			return cmd;
		}

		prikaz_kontajner = prikaz_kontajner->next;
	}
	return NULL;
}
