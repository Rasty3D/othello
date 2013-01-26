#include <iostream>
#include <fstream>
#include <list>
#include <string.h>

typedef struct
{
	unsigned int mask[2];
	unsigned int color[2];
}Tiles;

void printTiles(unsigned char *m, unsigned char *c, Tiles tiles)
{
	std::cout << tiles.mask[0] << ":" << tiles.mask[1];
	std::cout << " ";
	std::cout << tiles.color[0] << ":" << tiles.color[1];
	std::cout << std::endl;

	int i = 0;

	for (int k = 0; k < 8; k++)
	{
		std::cout << (int)m[i+0] << (int)m[i+1] << (int)m[i+2] << (int)m[i+3];
		std::cout << (int)m[i+4] << (int)m[i+5] << (int)m[i+6] << (int)m[i+7];
		std::cout << " ";
		std::cout << (int)c[i+0] << (int)c[i+1] << (int)c[i+2] << (int)c[i+3];
		std::cout << (int)c[i+4] << (int)c[i+5] << (int)c[i+6] << (int)c[i+7];
		std::cout << std::endl;
		i += 8;
	}
}

Tiles maskNcolor2Tiles(unsigned char *mask, unsigned char *color)
{
	Tiles tiles = {{0, 0}, {0, 0}};

	for (int i = 0; i < 32; i++)
	{
		tiles.mask[0]  +=  (mask[i]      & 0x01) << i;
		tiles.mask[1]  +=  (mask[i + 32] & 0x01) << i;
		tiles.color[0] += (color[i]      & 0x01) << i;
		tiles.color[1] += (color[i + 32] & 0x01) << i;
	}

	return tiles;
}

void lut_u(int i, int j, std::list<Tiles> &tilesList)
{
	unsigned char mask[64];
	unsigned char color[64];
	Tiles tiles;

	if (j <= 1)
		return;

	for (int k = 0; k < j - 1; k++)
	{
		memset(mask, 0, 64);
		memset(color, 0, 64);

		for (int l = 0; l < k + 2; l++)
			mask[i + (j - l - 1) * 8] = 1;

		color[i + (j - k - 2) * 8] = 1;

		tiles = maskNcolor2Tiles(mask, color);
		tilesList.push_back(tiles);
	}
}

void lut_d(int i, int j, std::list<Tiles> &tilesList)
{
	unsigned char mask[64];
	unsigned char color[64];
	Tiles tiles;

	if (j >= 6)
		return;

	for (int k = 0; k < 8 - j - 2; k++)
	{
		memset(mask, 0, 64);
		memset(color, 0, 64);

		for (int l = 0; l < k + 2; l++)
			mask[i + (j + l + 1) * 8] = 1;

		color[i + (j + k + 2) * 8] = 1;

		tiles = maskNcolor2Tiles(mask, color);
		tilesList.push_back(tiles);
	}
}

void lut_l(int i, int j, std::list<Tiles> &tilesList)
{
	unsigned char mask[64];
	unsigned char color[64];
	Tiles tiles;

	if (i <= 1)
		return;

	for (int k = 0; k < i - 1; k++)
	{
		memset(mask, 0, 64);
		memset(color, 0, 64);

		for (int l = 0; l < k + 2; l++)
			mask[(i - l - 1) + j * 8] = 1;

		color[(i - k - 2) + j * 8] = 1;

		tiles = maskNcolor2Tiles(mask, color);
		tilesList.push_back(tiles);
	}
}

void lut_r(int i, int j, std::list<Tiles> &tilesList)
{
	unsigned char mask[64];
	unsigned char color[64];
	Tiles tiles;

	if (i >= 6)
		return;

	for (int k = 0; k < 8 - i - 2; k++)
	{
		memset(mask, 0, 64);
		memset(color, 0, 64);

		for (int l = 0; l < k + 2; l++)
			mask[(i + l + 1) + j * 8] = 1;

		color[(i + k + 2) + j * 8] = 1;

		tiles = maskNcolor2Tiles(mask, color);
		tilesList.push_back(tiles);
	}
}

void lut_ul(int i, int j, std::list<Tiles> &tilesList)
{
	unsigned char mask[64];
	unsigned char color[64];
	Tiles tiles;

	if (j <= 1 || i <= 1)
		return;

	int dj = j - 1;
	int di = i - 1;
	int d = dj < di ? dj : di;

	for (int k = 0; k < d; k++)
	{
		memset(mask, 0, 64);
		memset(color, 0, 64);

		for (int l = 0; l < k + 2; l++)
			mask[(i - l - 1) + (j - l - 1) * 8] = 1;

		color[(i - k - 2) + (j - k - 2) * 8] = 1;

		tiles = maskNcolor2Tiles(mask, color);
		tilesList.push_back(tiles);
	}
}

void lut_ur(int i, int j, std::list<Tiles> &tilesList)
{
	unsigned char mask[64];
	unsigned char color[64];
	Tiles tiles;

	if (j <= 1 || i >= 6)
		return;

	int dj = j - 1;
	int di = 8 - i - 2;
	int d = dj < di ? dj : di;

	for (int k = 0; k < d; k++)
	{
		memset(mask, 0, 64);
		memset(color, 0, 64);

		for (int l = 0; l < k + 2; l++)
			mask[(i + l + 1) + (j - l - 1) * 8] = 1;

		color[(i + k + 2) + (j - k - 2) * 8] = 1;

		tiles = maskNcolor2Tiles(mask, color);
		tilesList.push_back(tiles);
	}
}

void lut_dl(int i, int j, std::list<Tiles> &tilesList)
{
	unsigned char mask[64];
	unsigned char color[64];
	Tiles tiles;

	if (j >= 6 || i <= 1)
		return;

	int dj = 8 - j - 2;
	int di = i - 1;
	int d = dj < di ? dj : di;

	for (int k = 0; k < d; k++)
	{
		memset(mask, 0, 64);
		memset(color, 0, 64);

		for (int l = 0; l < k + 2; l++)
			mask[(i - l - 1) + (j + l + 1) * 8] = 1;

		color[(i - k - 2) + (j + k + 2) * 8] = 1;

		tiles = maskNcolor2Tiles(mask, color);
		tilesList.push_back(tiles);
	}
}

void lut_dr(int i, int j, std::list<Tiles> &tilesList)
{
	unsigned char mask[64];
	unsigned char color[64];
	Tiles tiles;

	if (j >= 6 || i >= 6)
		return;

	int dj = 8 - j - 2;
	int di = 8 - i - 2;
	int d = dj < di ? dj : di;

	for (int k = 0; k < d; k++)
	{
		memset(mask, 0, 64);
		memset(color, 0, 64);

		for (int l = 0; l < k + 2; l++)
			mask[(i + l + 1) + (j + l + 1) * 8] = 1;

		color[(i + k + 2) + (j + k + 2) * 8] = 1;

		tiles = maskNcolor2Tiles(mask, color);
		tilesList.push_back(tiles);
	}
}

int main(int argc, char *argv[])
{
	// Variables
	std::list<Tiles> tilesList;
	std::list<Tiles>::iterator tilesListIt;
	int index = 0;
	unsigned int offsetTable[64 * 2];
	std::ofstream file;

	// Check arguments
	if (argc < 2)
	{
		std::cout << "Insert file name" << std::endl;
		return 0;
	}

	// Open file
	file.open(argv[1], std::ios::binary);

	if (!file)
	{
		std::cout << "Error opening file" << std::endl;
		return 0;
	}

	// Write temporal offset table
	file.write((char*)offsetTable, 64 * 4 * 2);

	// Move in the tiles
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			tilesList.clear();
			lut_u(i, j, tilesList);
			lut_d(i, j, tilesList);
			lut_l(i, j, tilesList);
			lut_r(i, j, tilesList);
			lut_ul(i, j, tilesList);
			lut_ur(i, j, tilesList);
			lut_dl(i, j, tilesList);
			lut_dr(i, j, tilesList);

			offsetTable[index++] = file.tellp();
			offsetTable[index++] = tilesList.size();

			for (tilesListIt = tilesList.begin(); tilesListIt != tilesList.end(); tilesListIt++)
				file.write((char*)&(*tilesListIt), 16);
		}
	}

	// Write offset table
	file.seekp(0);
	file.write((char*)offsetTable, 64 * 4 * 2);

	// Close file
	file.close();

	// Exit
	return 0;
}
