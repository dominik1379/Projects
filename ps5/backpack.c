#include <stdio.h>
#include <stdlib.h>
#include "backpack.h"

struct backpack* create_backpack(const int capacity)
{
	struct backpack* batoh = (struct backpack*)malloc(sizeof(struct backpack));
	batoh->capacity = capacity;
	batoh->size = 0;
	batoh->items = NULL;
	return batoh;
}

struct backpack* destroy_backpack(struct backpack* backpack)
{
	if (backpack == NULL)
		return NULL;
	destroy_containers(backpack->items);
	free(backpack);
	return NULL;
}

bool add_item_to_backpack(struct backpack* backpack, struct item* item)
{
	
	if (item == NULL || backpack == NULL)
		return false;

	if (backpack->size < backpack->capacity && item->properties & MOVABLE)
	{
		struct container* kontajner = create_container(backpack->items, ITEM, item);
		backpack->size++;
		if (backpack->items == NULL)
			backpack->items = kontajner;
		return true;
	}

	return false;
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item)
{
	if (backpack == NULL || item == NULL)
		return;

	if (backpack->items != NULL)
	{
		backpack->items = remove_container(backpack->items, item);
		backpack->size--;
	}
}

struct item* get_item_from_backpack(const struct backpack* backpack, char* name)
{
	if (backpack == NULL)
		return NULL;

	return (struct item*)get_from_container_by_name(backpack->items, name);
}
