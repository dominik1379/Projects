#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include <string.h>

char* vytvor_string_item(const char* retazec)
{
	char* novy_retazec = (char*)malloc(strlen(retazec) + 1);
	strcpy(novy_retazec, retazec);
	return novy_retazec;
}

struct item* create_item(char* name, char* description, unsigned int properties)
{
	if (name == NULL || description == NULL || name[0] == 0 || description[0] == 0)
		return NULL;

	struct item* predmet = (struct item*)malloc(sizeof(struct item));
	predmet->name = vytvor_string_item(name);
	predmet->description = vytvor_string_item(description);
	//predmet->name = name;
	//predmet->description = description;
	predmet->properties = properties;
	return predmet;
}

struct item* destroy_item(struct item* item)
{
	if (item == NULL)
		return NULL;
	if (item->name != NULL)
	free(item->name);
	if (item->description != NULL)
	free(item->description);
	free(item);
	return NULL;
}
