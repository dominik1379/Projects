#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "bmp.h"
#include <stdlib.h>


uint32_t Vypocitaj_padding2(uint32_t width)
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

struct bmp_header* read_bmp_header(FILE* stream)
{
	if (stream == NULL)
		return NULL;

	uint16_t typeBM = 0x4D42;
	struct bmp_header* header;
	header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
	fseek(stream, 0, SEEK_SET);
	if (fread(header, sizeof(struct bmp_header), 1, stream) == 1)
	{
		if (header->type == typeBM)
			return header;
	}
	free(header);
	return NULL;
}

struct pixel* read_data(FILE* stream, const struct bmp_header* header)
{
	if (stream == NULL || header == NULL)
		return NULL;

	struct pixel* pixels;
	int pocet = header->width * header->height;
	pixels = (struct pixel*)malloc(sizeof(struct pixel) * pocet);
	fseek(stream, sizeof(struct bmp_header), SEEK_SET);

	uint32_t padding = Vypocitaj_padding2(header->width);

	struct pixel* aktualnyPixel = pixels;
	for (uint32_t i = 0; i < header->height; i++)
	{
		for (uint32_t j = 0; j < header->width; j++)
		{
			if (fread(aktualnyPixel, sizeof(struct pixel), 1, stream) != 1)
			{
				free(pixels);
				return NULL;
			}
			aktualnyPixel++;
		}
		fseek(stream, padding, SEEK_CUR);
	}

	return pixels;
}

struct bmp_image* read_bmp(FILE* stream)
{
	if (stream == NULL)
		return NULL;

	struct bmp_header* hlavicka = read_bmp_header(stream);
	if (hlavicka == NULL)
	{
		fprintf(stderr, "Error: This is not a BMP file.\n");
		return NULL;
	}

	struct pixel* pixels = read_data(stream, hlavicka);
	if (pixels == NULL)
	{
		fprintf(stderr, "Error: Corrupted BMP file.\n");
		return NULL;
	}
	struct bmp_image* obrazok;
	obrazok = (struct bmp_image*)malloc(sizeof(struct bmp_image));
	obrazok->header = hlavicka;
	obrazok->data = pixels;
	return obrazok;
}


bool write_bmp(FILE* stream, const struct bmp_image* image)
{
	if (stream == NULL || image == NULL)
		return false;

	uint32_t padding = Vypocitaj_padding2(image->header->width);

	if (fwrite(image->header, sizeof(struct bmp_header), 1, stream) != 1)
		return false;


	struct pixel* aktualnyPixel = image->data;
	for (uint32_t i = 0; i < image->header->height; i++)
	{
		for (uint32_t j = 0; j < image->header->width; j++)
		{
			if (fwrite(aktualnyPixel, sizeof(struct pixel), 1, stream) != 1)
			{
				return false;
			}
			aktualnyPixel++;
		}
		fwrite(&PADDING_CHAR, sizeof(char), padding, stream);
	}
	return true;
}

void free_bmp_image(struct bmp_image* image)
{
	if (image != NULL)
	{
		free(image->header);
		free(image->data);
		free(image);
	}
}
