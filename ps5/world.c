#include <stdio.h>
#include <stdlib.h>
#include "world.h"
#include <string.h>

char* vytvor_string_world(const char* retazec)
{
	char* novy_retazec = (char*)malloc(strlen(retazec) + 1);
	strcpy(novy_retazec, retazec);
	return novy_retazec;
}

struct container* create_world()
{
	char* name;
	char* description;

	// [vytvorenie miestnosti]
	name = vytvor_string_world("Vychodny koniec udolia");
	description = vytvor_string_world("Zarastene udolie, ktore sa taha z vychodu na zapad. Vyzera monotonne a snad nekonecne dlho.");
	struct room* room1 = create_room(name, description);
	struct container* world = create_container(NULL, ROOM, room1);
	free(name);
	free(description);

	name = vytvor_string_world("Udolie");
	description = vytvor_string_world("Zarastene udolie, ktore sa taha z vychodu na zapad. Vyzera monotonne a snad nekonecne dlho.");
	struct room* room2 = create_room(name, description);
	create_container(world, ROOM, room2);
	free(name);
	free(description);

	name = vytvor_string_world("Udolie");
	description = vytvor_string_world("Zarastene udolie, ktore sa taha z vychodu na zapad. Vyzera monotonne a snad nekonecne dlho.");
	struct room* room3 = create_room(name, description);
	create_container(world, ROOM, room3);
	free(name);
	free(description);

	name = vytvor_string_world("Udolie");
	description = vytvor_string_world("Zarastene udolie, ktore sa taha z vychodu na zapad. Vyzera monotonne a snad nekonecne dlho.");
	struct room* room4 = create_room(name, description);
	create_container(world, ROOM, room4);
	free(name);
	free(description);

	name = vytvor_string_world("Udolie");
	description = vytvor_string_world("Zarastene udolie, ktore sa taha z vychodu na zapad. Vyzera monotonne a snad nekonecne dlho.");
	struct room* room5 = create_room(name, description);
	create_container(world, ROOM, room5);
	free(name);
	free(description);

	name = vytvor_string_world("Udolie");
	description = vytvor_string_world("Zarastene udolie, ktore sa taha z vychodu na zapad. Vyzera monotonne a snad nekonecne dlho.");
	struct room* room6 = create_room(name, description);
	create_container(world, ROOM, room6);
	free(name);
	free(description);

	name = vytvor_string_world("Udolie");
	description = vytvor_string_world("Zarastene udolie, ktore sa taha z vychodu na zapad. Vyzera monotonne a snad nekonecne dlho.");
	struct room* room7 = create_room(name, description);
	create_container(world, ROOM, room7);
	free(name);
	free(description);

	name = vytvor_string_world("Udolie");
	description = vytvor_string_world("Zarastene udolie, ktore sa taha z vychodu na zapad. Vyzera monotonne a snad nekonecne dlho.");
	struct room* room8 = create_room(name, description);
	create_container(world, ROOM, room8);
	free(name);
	free(description);

	name = vytvor_string_world("Udolie");
	description = vytvor_string_world("Zarastene udolie, ktore sa taha z vychodu na zapad. Vyzera monotonne a snad nekonecne dlho.");
	struct room* room9 = create_room(name, description);
	create_container(world, ROOM, room9);
	free(name);
	free(description);

	name = vytvor_string_world("Udolie");
	description = vytvor_string_world("Zarastene udolie, ktore sa taha z vychodu na zapad. Vyzera monotonne a snad nekonecne dlho.");
	struct room* room10 = create_room(name, description);
	create_container(world, ROOM, room10);
	free(name);
	free(description);

	name = vytvor_string_world("Udolie");
	description = vytvor_string_world("Zarastene udolie, ktore sa taha z vychodu na zapad. Vyzera monotonne a snad nekonecne dlho.");
	struct room* room11 = create_room(name, description);
	create_container(world, ROOM, room11);
	free(name);
	free(description);

	name = vytvor_string_world("Udolie");
	description = vytvor_string_world("Zarastene udolie, ktore sa taha z vychodu na zapad. Vyzera monotonne a snad nekonecne dlho.");
	struct room* room12 = create_room(name, description);
	create_container(world, ROOM, room12);
	free(name);
	free(description);

	name = vytvor_string_world("Udolie");
	description = vytvor_string_world("Zarastene udolie, ktore sa taha z vychodu na zapad. Vyzera monotonne a snad nekonecne dlho.");
	struct room* room13 = create_room(name, description);
	create_container(world, ROOM, room13);
	free(name);
	free(description);

	name = vytvor_string_world("Udolie");
	description = vytvor_string_world("Zarastene udolie, ktore sa taha z vychodu na zapad. Vyzera monotonne a snad nekonecne dlho.");
	struct room* room14 = create_room(name, description);
	create_container(world, ROOM, room14);
	free(name);
	free(description);

	name = vytvor_string_world("Zapadny koniec udolia");
	description = vytvor_string_world("Zarastene udolie, ktore sa taha z vychodu na zapad. Vyzera monotonne a snad nekonecne dlho.");
	struct room* room15 = create_room(name, description);
	create_container(world, ROOM, room15);
	free(name);
	free(description);



	// [vytvorenie predmetov]
	// Kamen; ziadne vyuzitie (da sa nosit v batohu)
	name = vytvor_string_world("Kamen");
	description = vytvor_string_world("Obycajny kamen.");
	struct item* item_kamen1 = create_item(name, description, MOVABLE);
	add_item_to_room(room1, item_kamen1);
	free(name);
	free(description);

	// Socha; ziadne vyuzitie
	name = vytvor_string_world("Socha");
	description = vytvor_string_world("Socha slobody prerastena papradim.");
	struct item* item_socha = create_item(name, description, NONE);
	add_item_to_room(room1, item_socha);
	free(name);
	free(description);

	// Kamen; ziadne vyuzitie (da sa nosit v batohu)
	name = vytvor_string_world("Kamen");
	description = vytvor_string_world("Obycajny kamen.");
	struct item* item_kamen2 = create_item(name, description, MOVABLE);
	add_item_to_room(room1, item_kamen2);
	free(name);
	free(description);

	// Modry kluc; potrebny na otvorenie farebnej krabice
	name = vytvor_string_world("Modry kluc");
	description = vytvor_string_world("Kluc z neznameho materialu. Jemne ziari na modro.");
	struct item* item_modry_kluc = create_item(name, description, MOVABLE | USABLE);
	add_item_to_room(room10, item_modry_kluc);
	free(name);
	free(description);

	// Cerveny kluc; potrebny na otvorenie farebnej krabice
	name = vytvor_string_world("Cerveny kluc");
	description = vytvor_string_world("Kluc z neznameho materialu. Jemne ziari na cerveno.");
	struct item* item_cerveny_kluc = create_item(name, description, MOVABLE | USABLE);
	add_item_to_room(room15, item_cerveny_kluc);
	free(name);
	free(description);

	// Farebna krabica;
	// po preskumani ziska novy popis "Krabica z neznameho materialu prirastena ku skale. Ma na sebe dva zamky."; strati EXAMINABLE
	// po pouziti dvoch klucov (az po preskumani) ziska krabica OPENABLE
	// po otvoreni krabice je uspesny koniec hry
	name = vytvor_string_world("Farebna krabica");
	description = vytvor_string_world("Krabica z neznameho materialu prirastena ku skale. Na krabici sa nachadza cerveny zamok.");
	struct item* item_farebna_krabica = create_item(name, description, EXAMINABLE);
	add_item_to_room(room1, item_farebna_krabica);
	free(name);
	free(description);



	// [prepojenie miestnosti]
	// linearne usporiadane miestnosti z vychodu na zapad
	set_exits_from_room(room1, NULL, NULL, NULL, room2);
	set_exits_from_room(room2, NULL, NULL, room1, room3);
	set_exits_from_room(room3, NULL, NULL, room2, room4);
	set_exits_from_room(room4, NULL, NULL, room3, room5);
	set_exits_from_room(room5, NULL, NULL, room4, room6);
	set_exits_from_room(room6, NULL, NULL, room5, room7);
	set_exits_from_room(room7, NULL, NULL, room6, room8);
	set_exits_from_room(room8, NULL, NULL, room7, room9);
	set_exits_from_room(room9, NULL, NULL, room8, room10);
	set_exits_from_room(room10, NULL, NULL, room9, room11);
	set_exits_from_room(room11, NULL, NULL, room10, room12);
	set_exits_from_room(room12, NULL, NULL, room11, room13);
	set_exits_from_room(room13, NULL, NULL, room12, room14);
	set_exits_from_room(room14, NULL, NULL, room13, room15);
	set_exits_from_room(room15, NULL, NULL, room14, NULL);

	return world;
}

struct container* add_room_to_world(struct container* world, struct room* room)
{
	if (room == NULL)
		return NULL;
	// ak miestnost uz existuje, vrat NULL
	struct room* miestnost = get_room(world, room->name);
	if (miestnost != NULL)
		return NULL;

	// pridaj miestnost do sveta
	struct container* kontajner = create_container(world, ROOM, room);
	return kontajner;
}

struct container* destroy_world(struct container* world)
{
	if (world != NULL)
	{
		destroy_containers(world);
	}

	return NULL;
}

struct room* get_room(struct container* world, char* name)
{
	if (world == NULL || name == NULL)
		return NULL;

	struct container* aktualny_kontajner = world;
	while (aktualny_kontajner != NULL)
	{
		if (strcmp(aktualny_kontajner->room->name, name) == 0)
		{
			return aktualny_kontajner->room;
		}
		aktualny_kontajner = aktualny_kontajner->next;
	}

	return NULL;
}
