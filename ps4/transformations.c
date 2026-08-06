#include <stdio.h>
#include "transformations.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

void copyheader(struct bmp_header* destination, struct bmp_header* source)
{
	destination->bpp = source->bpp;
	destination->compression = source->compression;
	destination->dib_size = source->dib_size;
	destination->height = source->height;
	destination->image_size = source->image_size;
	destination->important_colors = source->important_colors;
	destination->num_colors = source->num_colors;
	destination->offset = source->offset;
	destination->planes = source->planes;
	destination->reserved1 = source->reserved1;
	destination->reserved2 = source->reserved2;
	destination->size = source->size;
	destination->type = source->type;
	destination->width = source->width;
	destination->x_ppm = source->x_ppm;
	destination->y_ppm = source->y_ppm;
}

uint32_t Vypocitaj_padding(uint32_t width)
{
	int pixelsPerRow = width * sizeof(struct pixel);
	int padding;
	if (pixelsPerRow % 4 == 0)
		padding = 0;
	else if ((pixelsPerRow + 1) % 4 == 0)
		padding = 1;
	else if ((pixelsPerRow + 2) % 4 == 0)
		padding = 2;
	else
		padding = 3;
	return padding;
}

uint32_t vypocitaj_image_size(uint32_t width, uint32_t height)
{
    uint32_t padding = Vypocitaj_padding(width);
    return (sizeof(struct pixel) * width * height) + (height * padding);
}

uint32_t vypocitaj_file_size(uint32_t width, uint32_t height)
{
    return sizeof(struct bmp_header) + vypocitaj_image_size(width, height);
}

struct bmp_image* flip_horizontally(const struct bmp_image* image)
{
	if (image == NULL)
		return NULL;

	struct bmp_image* obrazok;
	obrazok = (struct bmp_image*)malloc(sizeof(struct bmp_image));
	obrazok->data = (struct pixel*)malloc(sizeof(struct pixel) * image->header->height * image->header->width);
	obrazok->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
	copyheader(obrazok->header, image->header);

	for (uint32_t i = 0; i < image->header->height; i++)
	{
		for (uint32_t j = 0; j < image->header->width; j++)
		{
			int MaxRowIndex = image->header->width - 1;
			int Riadok = i * image->header->width;

			obrazok->data[Riadok + j].blue = image->data[Riadok + MaxRowIndex - j].blue;
			obrazok->data[Riadok + j].green = image->data[Riadok + MaxRowIndex - j].green;
			obrazok->data[Riadok + j].red = image->data[Riadok + MaxRowIndex - j].red;
		}
	}
	return obrazok;
}

struct bmp_image* flip_vertically(const struct bmp_image* image)
{
	if (image == NULL)
		return NULL;

	struct bmp_image* obrazok;
	obrazok = (struct bmp_image*)malloc(sizeof(struct bmp_image));
	obrazok->data = (struct pixel*)malloc(sizeof(struct pixel) * image->header->height * image->header->width);
	obrazok->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
	copyheader(obrazok->header, image->header);

	for (uint32_t j = 0; j < image->header->width; j++)
	{
		for (uint32_t i = 0; i < image->header->height; i++)
		{
			int RiadokLavy = i * image->header->width;
			int RiadokPravy = (image->header->height - i - 1) * image->header->width;

			obrazok->data[RiadokLavy + j].blue = image->data[RiadokPravy + j].blue;
			obrazok->data[RiadokLavy + j].green = image->data[RiadokPravy + j].green;
			obrazok->data[RiadokLavy + j].red = image->data[RiadokPravy + j].red;
		}
	}
	return obrazok;
}

struct bmp_image* rotate_right(const struct bmp_image* image)
{
	if (image == NULL)
		return NULL;

	struct bmp_image* obrazok;
	obrazok = (struct bmp_image*)malloc(sizeof(struct bmp_image));
	obrazok->data = (struct pixel*)malloc(sizeof(struct pixel) * image->header->height * image->header->width);
	obrazok->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
	copyheader(obrazok->header, image->header);
	obrazok->header->height = image->header->width;
	obrazok->header->width = image->header->height;
	obrazok->header->size = vypocitaj_file_size(obrazok->header->width, obrazok->header->height);
	obrazok->header->image_size = vypocitaj_image_size(obrazok->header->width, obrazok->header->height);

	uint32_t r2 = 0;
	uint32_t s2 = 0;

	for (uint32_t r = 0; r < image->header->height; r++)
	{
		for (uint32_t s = 0; s < image->header->width; s++)
		{
			obrazok->data[r2 * obrazok->header->width + s2].blue = image->data[r * image->header->width + image->header->width - 1 - s].blue;
			obrazok->data[r2 * obrazok->header->width + s2].green = image->data[r * image->header->width + image->header->width - 1 - s].green;
			obrazok->data[r2 * obrazok->header->width + s2].red = image->data[r * image->header->width + image->header->width - 1 - s].red;
			r2++;
		}
		s2++;
		r2 = 0;
	}
	return obrazok;
}

struct bmp_image* rotate_left(const struct bmp_image* image)
{
	if (image == NULL)
		return NULL;

	struct bmp_image* obrazok;
	obrazok = (struct bmp_image*)malloc(sizeof(struct bmp_image));
	obrazok->data = (struct pixel*)malloc(sizeof(struct pixel) * image->header->height * image->header->width);
	obrazok->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
	copyheader(obrazok->header, image->header);
	obrazok->header->height = image->header->width;
	obrazok->header->width = image->header->height;
	obrazok->header->size = vypocitaj_file_size(obrazok->header->width, obrazok->header->height);
	obrazok->header->image_size = vypocitaj_image_size(obrazok->header->width, obrazok->header->height);

	uint32_t r2 = 0;
	uint32_t s2 = 0;

	for (uint32_t r = 0; r < image->header->height; r++)
	{
		for (uint32_t s = 0; s < image->header->width; s++)
		{
			obrazok->data[r2 * obrazok->header->width + obrazok->header->width - 1 - s2].blue = image->data[r * image->header->width + s].blue;
			obrazok->data[r2 * obrazok->header->width + obrazok->header->width - 1 - s2].green = image->data[r * image->header->width + s].green;
			obrazok->data[r2 * obrazok->header->width + obrazok->header->width - 1 - s2].red = image->data[r * image->header->width + s].red;
			r2++;
		}
		s2++;
		r2 = 0;
	}
	return obrazok;
}
struct bmp_image* crop(const struct bmp_image* image, const uint32_t start_y, const uint32_t start_x, const uint32_t height, const uint32_t width)
{
	if (image == NULL ||
		start_x < 0 ||
		start_y < 0 ||
		height < 1 ||
		width < 1 ||
		start_x + width > image->header->width ||
		start_y + height > image->header->height
		)
		return NULL;

	struct bmp_image* obrazok;
	obrazok = (struct bmp_image*)malloc(sizeof(struct bmp_image));
	obrazok->data = (struct pixel*)malloc(sizeof(struct pixel) * height * width);
	obrazok->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
	copyheader(obrazok->header, image->header);
	obrazok->header->height = height;
	obrazok->header->width = width;
	obrazok->header->size = vypocitaj_file_size(obrazok->header->width, obrazok->header->height);
	obrazok->header->image_size = vypocitaj_image_size(obrazok->header->width, obrazok->header->height);
	int y = image->header->height - height - start_y;

	for (uint32_t r = 0; r < height; r++)
	{
		for (uint32_t s = 0; s < width; s++)
		{
			obrazok->data[r * width + s].blue = image->data[(r + y) * image->header->width + (s + start_x)].blue;
			obrazok->data[r * width + s].green = image->data[(r + y) * image->header->width + (s + start_x)].green;
			obrazok->data[r * width + s].red = image->data[(r + y) * image->header->width + (s + start_x)].red;
		}
	}
	return obrazok;
}

struct bmp_image* scale(const struct bmp_image* image, float factor)
{
	if (image == NULL || factor < 0)
		return NULL;

	uint32_t NewWidth = round((double)image->header->width * factor);
	uint32_t NewHeight = round((double)image->header->height * factor);

	struct bmp_image* obrazok;
	obrazok = (struct bmp_image*)malloc(sizeof(struct bmp_image));
	obrazok->data = (struct pixel*)malloc(sizeof(struct pixel) * NewWidth * NewHeight);
	obrazok->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
	copyheader(obrazok->header, image->header);
	obrazok->header->height = NewHeight;
	obrazok->header->width = NewWidth;
	obrazok->header->size = vypocitaj_file_size(obrazok->header->width, obrazok->header->height);
	obrazok->header->image_size = vypocitaj_image_size(obrazok->header->width, obrazok->header->height);

	//for (uint32_t r = 0; r < NewHeight; r++)
	//{
	//	for (uint32_t s = 0; s < NewWidth; s++)
	//	{
	//		int NewS = (float)s * (float)image->header->width / (float)NewWidth;
	//		int NewR = (float)r * (float)image->header->height / (float)NewHeight;

	//		int NewR_vpravo = (image->header->height - 1) - NewR;
	//		int r_vlavo = (NewHeight - 1) - r;

	//		obrazok->data[r_vlavo * NewWidth + s].blue = image->data[NewR_vpravo * image->header->width + NewS].blue;
	//		obrazok->data[r_vlavo * NewWidth + s].green = image->data[NewR_vpravo * image->header->width + NewS].green;
	//		obrazok->data[r_vlavo * NewWidth + s].red = image->data[NewR_vpravo * image->header->width + NewS].red;
	//	}
	//}

	for (uint32_t r = 0; r < NewHeight; r++)
	{
		for (uint32_t s = 0; s < NewWidth; s++)
		{
			int NewS = (float)s * (float)image->header->width / (float)NewWidth;
			int NewR = (float)r * (float)image->header->height / (float)NewHeight;

			obrazok->data[r * NewWidth + s].blue = image->data[NewR * image->header->width + NewS].blue;
			obrazok->data[r * NewWidth + s].green = image->data[NewR * image->header->width + NewS].green;
			obrazok->data[r * NewWidth + s].red = image->data[NewR * image->header->width + NewS].red;
		}
	}

	return obrazok;
}

struct bmp_image* extract(const struct bmp_image* image, const char* colors_to_keep)
{
	if (image == NULL || colors_to_keep == NULL)
		return NULL;

	bool red = false;
	bool green = false;
	bool blue = false;

	for (int i = 0; colors_to_keep[i] != 0; i++)
	{
		if (colors_to_keep[i] == 'r')
			red = true;
		else if (colors_to_keep[i] == 'g')
			green = true;
		else if (colors_to_keep[i] == 'b')
			blue = true;
		else
			return NULL;
	}
	struct bmp_image* obrazok;
	obrazok = (struct bmp_image*)malloc(sizeof(struct bmp_image));
	obrazok->data = (struct pixel*)malloc(sizeof(struct pixel) * image->header->height * image->header->width);
	obrazok->header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
	copyheader(obrazok->header, image->header);



	for (uint32_t r = 0; r < image->header->height; r++)
	{
		for (uint32_t s = 0; s < image->header->width; s++)
		{
			if (blue)
				obrazok->data[r * image->header->width + s].blue = image->data[r * image->header->width + s].blue;
			else
				obrazok->data[r * image->header->width + s].blue = 0;
			if (green)
				obrazok->data[r * image->header->width + s].green = image->data[r * image->header->width + s].green;
			else
				obrazok->data[r * image->header->width + s].green = 0;
			if (red)
				obrazok->data[r * image->header->width + s].red = image->data[r * image->header->width + s].red;
			else
				obrazok->data[r * image->header->width + s].red = 0;
		}
	}
	return obrazok;
}
