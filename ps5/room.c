#include <stdio.h>
#include <stdlib.h>
#include "room.h"
#include <string.h>
char* vytvor_string_room(const char* retazec)
{
	char* novy_retazec = (char*)malloc(strlen(retazec) + 1);
	strcpy(novy_retazec, retazec);
	return novy_retazec;
}

struct room* create_room(char* name, char* description)
{
	if (name == NULL || description == NULL || name[0] == 0 || description[0] == 0)
		return NULL;

	struct room* miestnost = (struct room *)malloc(sizeof(struct room));
	miestnost->name = vytvor_string_room(name);
	miestnost->description = vytvor_string_room(description);
	miestnost->east = NULL;
	miestnost->north = NULL;
	miestnost->south = NULL;
	miestnost->west = NULL;
	miestnost->items = NULL;

	return miestnost;
}

struct room* destroy_room(struct room* room)
{
	if (room != NULL)
	{
		destroy_containers(room->items);
		if(room->name != NULL)
		free(room->name);
		if (room->description != NULL)
		free(room->description);
		free(room);
	}
	return NULL;
}

void set_exits_from_room(struct room* room, struct room* north, struct room* south, struct room* east, struct room* west)
{
	if (room == NULL)
		return;

	room->north = north;
	room->south = south;
	room->east = east;
	room->west = west;
}

void show_room(const struct room* room)
{
	if (room == NULL)
		return;

	printf("%s\n\n", room->description);

	printf("Mozne vychody z miestnosti:\n");
	if (room->north != NULL)
		printf("   sever\n");
	if (room->south != NULL)
		printf("   juh\n");
	if (room->east != NULL)
		printf("   vychod\n");
	if (room->west != NULL)
		printf("   zapad\n");

	printf("\nVidis:\n");
	struct container* kontajner_predmetov = room->items;
	while (kontajner_predmetov != NULL)
	{
		printf("   %s\n", kontajner_predmetov->item->name);
		kontajner_predmetov = kontajner_predmetov->next;
	}
}

void delete_item_from_room(struct room* room, struct item* item)
{
	if (room == NULL || item == NULL)
		return;
	room->items = remove_container(room->items, item);
}


void add_item_to_room(struct room* room, struct item* item)
{
	if (item == NULL || room == NULL)
		return;

	struct container* novyKontajner = create_container(room->items, ITEM, item);
	if (room->items == NULL)
		room->items = novyKontajner;
}

struct item* get_item_from_room(const struct room* room, const char* name)
{
	if (room == NULL)
		return NULL;

	return (struct item*)get_from_container_by_name(room->items, name);
}
