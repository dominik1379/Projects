#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "container.h"

bool is_equal_container(char* str1, char* str2)
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

struct container* create_container(struct container* first, enum container_type type, void* entry)
{
	if ((first != NULL && type != first->type) || entry == NULL)
		return NULL;

	struct container* kontajner = (struct container*)malloc(sizeof(struct container));
	struct container* posledny = first;
	kontajner->next = NULL;
	kontajner->type = type;
	switch (type) {
	case ITEM:
		kontajner->item = (struct item*)entry;
		break;

	case ROOM:
		kontajner->room = (struct room*)entry;
		break;

	case COMMAND:
		kontajner->command = (struct command*)entry;
		break;
		
	default: //case TEXT:
		kontajner->text = (char*)entry;
		break;
	}

	if (posledny != NULL)
	{
		while (posledny->next != NULL)
		{
			posledny = posledny->next;
		}
		posledny->next = kontajner;
	}
	return kontajner;
}

void destroy_container_content(struct container* container)
{
	switch (container->type) {
	case ITEM:
		destroy_item(container->item);
		break;

	case ROOM:
		destroy_room(container->room);
		break;

	case COMMAND:
		destroy_command(container->command);
		break;

	default: //case TEXT:
		free(container->text);
		break;
	}
}

struct container* destroy_containers(struct container* first)
{
	if (first == NULL)
		return NULL;

	if (first->next != NULL)
	{
		destroy_containers(first->next);
	}
	destroy_container_content(first);
	free(first);
	return NULL;
}

void* get_from_container_by_name(struct container* first, const char* name)
{
	if (name == NULL)
		return NULL;

	while (first != NULL)
	{
		switch (first->type) {
		case ROOM:
			if (is_equal_container(first->room->name, (char*)name))
			{
				return first->room;
			}
			break;
		case ITEM:
			if (is_equal_container(first->item->name, (char*)name))
			{
				return first->item;
			}
			break;
		case COMMAND:
			if (is_equal_container(first->command->name, (char*)name))
			{
				return first->command;
			}
			break;
		default: //case TEXT:
			if (is_equal_container(first->text, (char*)name))
			{
				return first->text;
			}
			break;
		}
		first = first->next;
	}
	return NULL;
}
char* get_kontajner_name(struct container* kontajner)
{
	switch (kontajner->type)
	{
	case ROOM:
		return kontajner->room->name;

	case ITEM:
		return kontajner->item->name;

	case COMMAND:
		return kontajner->command->name;

	default: //case TEXT:
		return kontajner->text;
	}
}

char* get_entry_name(enum container_type type, void* entry)
{
	switch (type)
	{
	case ROOM:
		return  ((struct room*)entry)->name;

	case ITEM:
		return ((struct item*)entry)->name;

	case COMMAND:
		return ((struct command*)entry)->name;

	default: //case TEXT:
		return (char*)entry;
	}
}

struct container* remove_container(struct container* first, void* entry)
{
	if (first == NULL || entry == NULL)
		return first;

	struct container* predosly = NULL;
	struct container* aktualny = first;
	char* entry_name = get_entry_name(first->type, entry);
	while (aktualny != NULL)
	{
		char* container_name = get_kontajner_name(aktualny);
		if (strcmp(container_name, entry_name) == 0)
		{
			if (predosly == NULL)
			{
				first = aktualny->next;
			}
			else
			{
				predosly->next = aktualny->next;
			}
			free(aktualny);
			return first;
		}
		predosly = aktualny;
		aktualny = aktualny->next;
	}
	return first;
}
