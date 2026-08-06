#include <stdio.h>
#include "container.h"
#include "world.h"
#include "room.h"
#include "parser.h"
#include "item.h"
#include "game.h"
#include "command.h"
#include "backpack.h"

int main()
{

	create_container(NULL, ROOM, NULL);
	destroy_containers(NULL);
	get_from_container_by_name(NULL, NULL);
	remove_container(NULL, NULL);
	create_room(NULL, NULL);
	destroy_room(NULL);
	set_exits_from_room(NULL, NULL, NULL, NULL, NULL);
	show_room(NULL);
	delete_item_from_room(NULL, NULL);
	add_item_to_room(NULL, NULL);
	get_item_from_room(NULL, NULL);
	create_command(NULL, NULL, NULL, 0);
	destroy_command(NULL);
	play_game(NULL);
	create_game();
	destroy_game(NULL);
	execute_command(NULL, NULL);
	create_parser();
	destroy_parser(NULL);
	parse_input(NULL, NULL);
	create_world();
	add_room_to_world(NULL, NULL);
	destroy_world(NULL);
	get_room(NULL, NULL);
	create_item(NULL, NULL, MOVABLE);
	destroy_item(NULL);
	create_backpack(0);
	destroy_backpack(NULL);
	add_item_to_backpack(NULL, NULL);
	delete_item_from_backpack(NULL, NULL);
	get_item_from_backpack(NULL, NULL);


	return 0;
}
