#include <stdio.h>
#include <stdlib.h>
#include "command.h"
#include <string.h>

char* vytvor_string_command(const char* retazec)
{
	char* novy_retazec = (char*)malloc(strlen(retazec) + 1);
	strcpy(novy_retazec, retazec);
	return novy_retazec;
}

struct command* create_command(char* name, char* description, char* pattern, size_t nmatch)
{
	if (name == NULL || description == NULL || name[0] == 0 || description[0] == 0)
		return NULL;

	struct command* prikaz = (struct command*)malloc(sizeof(struct command));
	prikaz->name = vytvor_string_command(name);
	prikaz->description = vytvor_string_command(description);
	//prikaz->name = name;
	//prikaz->description = description;
	prikaz->nmatch = nmatch;
	if (pattern != NULL) {
		if (regcomp(&prikaz->preg, pattern, REG_ICASE | REG_EXTENDED) != 0) {
			// Regular expression could not be compiled.
			free(pattern);
			return NULL;
		}
		free(pattern);
	}
	
	prikaz->groups = NULL;

	return prikaz;
}

struct command* destroy_command(struct command* command)
{
	if (command != NULL)
	{
		if (command->groups != NULL)
		{
			int i = 0;
			while (command->groups[i] != NULL)
			{
				free(command->groups[i]);
				i++;
			}
			free(command->groups);
			command->groups = NULL;
		}
		if(command->name != NULL)
		free(command->name);
		if (command->description != NULL)
		free(command->description);
		regfree(&command->preg);
		free(command);
	}
	return NULL;
}
