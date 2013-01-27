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
	Tiles tiles;
	int index = 0;
	unsigned int offsetTable[64 * 2];
	std::ofstream file;

	// Move in the tiles
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			offsetTable[index] = tilesList.size();

			lut_u(i, j, tilesList);
			lut_d(i, j, tilesList);
			lut_l(i, j, tilesList);
			lut_r(i, j, tilesList);
			lut_ul(i, j, tilesList);
			lut_ur(i, j, tilesList);
			lut_dl(i, j, tilesList);
			lut_dr(i, j, tilesList);

			offsetTable[index + 1] = tilesList.size() - offsetTable[index];
			index += 2;
		}
	}


		/* Save header file */

	// Open file
	file.open("lut.h");

	if (!file)
	{
		std::cout << "Error opening file" << std::endl;
		return 0;
	}

	// Write header
	file << "/*\n";
	file << " * Autogenerated header file: lut.h\n";
	file << " */\n";
	file << "\n";
	file << "#ifndef OTHELLO_LUT\n";
	file << "#define OTHELLO_LUT\n";
	file << "\n";

	// Write types
	file << "/*\n";
	file << " * TYPES\n";
	file << " */\n";
	file << "\n";
	file << "typedef struct\n";
	file << "{\n";
	file << "  unsigned int mask[2];\n";
	file << "  unsigned int color[2];\n";
	file << "}Othello_LUT;\n";
	file << "\n";

	// Write variables
	file << "\n";
	file << "/*\n";
	file << " * VARIABLES\n";
	file << " */\n";
	file << "\n";
	file << "extern unsigned int othello_LUTOffset[128];\n";
	file << "extern Othello_LUT othello_LUT[" << tilesList.size() << "];\n";
	file << "\n";

	// Write footer
	file << "#endif  /* OTHELLO_LUT */\n";

	// Close file
	file.close();


		/* Save source file */

	// Save source file with all the information
	file.open("lut.cpp");

	if (!file)
	{
		std::cout << "Error opening file" << std::endl;
		return 0;
	}

	// Write header
	file << "/*\n";
	file << " * Autogenerated source file: lut.cpp\n";
	file << " */\n";
	file << "\n";

	// Write include files
	file << "/*\n";
	file << " * INCLUDES\n";
	file << " */\n";
	file << "\n";
	file << "#include \"lut.h\"\n";
	file << "\n";

	// Write variables
	file << "\n";
	file << "/*\n";
	file << " * VARIABLES\n";
	file << " */\n";
	file << "\n";

	// Write offset table
	file << "unsigned int othello_LUTOffset[128] = {\n";

	for (int i = 0; i < 63; i++)
		file << "  " << offsetTable[i * 2] << ", " << offsetTable[i * 2 + 1] << ",\n";
	file << "  " << offsetTable[126] << ", " << offsetTable[127] << "};\n";

	file << "\n";

	// Write tiles
	file << "Othello_LUT othello_LUT[" << tilesList.size() << "] = {\n";

	while (!tilesList.empty())
	{
		tiles = tilesList.front();

		file << "  {{0x" << std::hex << tiles.mask[0];
		file <<   ", 0x" << std::hex << tiles.mask[1];
		file << "}, {0x" << std::hex << tiles.color[0];
		file <<   ", 0x" << std::hex << tiles.color[1] << "}}";

		tilesList.pop_front();

		if (tilesList.empty())
			file << "};\n";
		else
			file << ",\n";
	}

	// Close file
	file.close();

	// Exit
	return 0;
}
