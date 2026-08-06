#include <stdio.h>
#include "k.h"
#include "hof.h"
#include "ui.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(){
add_random_tile(struct game *game);
render(const struct game game);
// game is won
struct game game = {
    .board = {
        {'A', 'B', 'C', 'D'},
        {'E', 'F', 'G', 'H'},
        {'I', 'J', 'K', 'A'},
        {'B', 'C', 'D', 'E'}
    },
    .score = 0
};

printf("is won: %d\n", is_game_won(game));
// stdout: 1

// game is not won
struct game game = {
    .board = {
        {'A', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', 'A'},
        {'B', ' ', ' ', ' '}
    },
    .score = 0
};

printf("is not won: %d\n", is_game_won(game));
// stdout: 0

// another move is possible
struct game game = {
    .board = {
        {'A', 'A', 'C', 'D'},
        {'A', 'F', 'G', 'H'},
        {'I', 'J', 'J', 'A'},
        {'B', 'C', 'D', 'E'}
    },
    .score = 0
};

printf("is move possible: %d\n", is_move_possible(game));
// stdout: 1

// another move is not possible
struct game game = {
    .board = {
        {'A', 'B', 'C', 'D'},
        {'E', 'F', 'G', 'H'},
        {'I', 'J', 'K', 'A'},
        {'B', 'C', 'D', 'E'}
    },
    .score = 0
};

printf("is move possible: %d\n", is_move_possible(game));
// stdout: 0

// wrong call
bool result = update(&game, 1, 1);
// result = false
// move right
struct game game = {
    .board = {
        {'A', ' ', ' ', ' '},
        {'B', ' ', ' ', 'B'},
        {'C', 'C', 'C', ' '},
        {'D', 'D', 'D', 'D'}
    },
    .score = 0
};
printf("result: %d\n", result);

bool result = update(&game, 0, 1);
/*
game = {
    .board = {
        {' ', ' ', ' ', 'A'},
        {' ', ' ', ' ', 'C'},
        {' ', ' ', 'C', 'D'},
        {' ', ' ', 'E', 'E'}
    },
    .score = 88
};
result = true;
*/
// can't move left
struct game game = {
    .board = {
        {'A', 'B', 'C', 'D'},
        {'A', 'B', 'C', 'D'},
        {'A', 'B', 'C', 'D'},
        {'A', 'B', 'C', 'D'}
    },
    .score = 1234
};
printf("result: %d\n", result);
bool result = update(&game, 0, -1);
/*
game = {
    .board = {
        {'A', 'B', 'C', 'D'},
        {'A', 'B', 'C', 'D'},
        {'A', 'B', 'C', 'D'},
        {'A', 'B', 'C', 'D'}
    },
    .score = 1234
};
result = false;
*/
// case 1: the list is empty
struct player list[10];
int size = 0;
struct player player = {
    .name = "John",
    .score = 100
};
printf("result: %d\n", result);
bool result = add_player(list, &size, player);

/* result = true, size = 1
list:
John 100
*/
// case 2: the list contains 10 entries
/*
file: score
manager 5000
manager 4000
manager 3000
manager 2000
manager 1000
manager 500
manager 400
manager 300
manager 200
manager 100
*/

struct player list[10];
struct player player = {
    .name = "john",
    .score = 400
};
int size = load(list);
bool result = add_player(list, &size, player);

/* result = true, size = 10
list:
manager 5000
manager 4000
manager 3000
manager 2000
manager 1000
manager 500
john 400
manager 400
manager 300
manager 200
*/
// case 3: player has same score as last player in HOF
/*
file: score
manager 5000
manager 4000
manager 3000
manager 2000
manager 1000
manager 500
manager 400
manager 300
manager 200
manager 100
*/

struct player list[10];
struct player player = {
    .name = "john",
    .score = 100
};
int size = load(list);
bool result = add_player(list, &size, player);

/* result = true, size = 10
list:
manager 5000
manager 4000
manager 3000
manager 2000
manager 1000
manager 500
manager 400
manager 300
manager 200
john 100
*/
struct player list[10];
struct player player = {
    .name = "john",
    .score = 100
};
int size = load(list);
bool result = save(list, size);


return 0;
}
