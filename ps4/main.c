#include <stdio.h>
#include "bmp.h"
#include "transformations.h"

int main()
{
    read_bmp_header(NULL);
	read_data(NULL, NULL);
	read_bmp(NULL);
	write_bmp(NULL, NULL);
	free_bmp_image(NULL);
    flip_horizontally(NULL);
	flip_vertically(NULL);
	rotate_right(NULL);
	rotate_left(NULL);
	scale(NULL, 0);
	crop(NULL, 0, 0, 0, 0);
	extract(NULL, NULL);
    return 0;
}
