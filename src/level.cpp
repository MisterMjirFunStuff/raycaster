#include "level.h"
#include "constants.h"
#include <fstream>

#include <iostream>

static bool checkCharNum(char c);

Level::Level()
{
	raw.reserve(8 * 8);
}

int Level::load(std::string fpath)
{
	raw.clear();

	std::fstream file;
	file.open(fpath, std::ios::in);
	if (!file.is_open())
		return -1; // Could not open file

	char tempChar;
	std::string property;
	std::string value;
	while (!file.eof())
	{
		// TODO: Improve file parsing code
		file.get(tempChar);
		if (tempChar == '@')
		{
			do
			{
				file.get(tempChar);
				property += tempChar;
			} while (file.peek() != ':');

			file.get(); // Skips past the ':'

			if (!property.compare("SIZE"))
			{
				do
				{
					file.get(tempChar);
					if (tempChar == 'x' || tempChar == '\n')
					{
						try
						{
							if (tempChar == 'x')
								size.x = std::stoi(value);
							else
								size.y = std::stoi(value);
						}
						catch (std::exception e)
						{
							// Bad number
							return -1;
						}

						value.clear();
					}
					else
					{
						if (checkCharNum(tempChar))
						{
							value += tempChar;
						}
					}
				} while (file.peek() != '@' && file.peek() != EOF);

				if (file.peek() == EOF)
					raw.push_back(std::stoi(value));
			}
			else if (!property.compare("SPAWN"))
			{
				do
				{
					file.get(tempChar);
					if (tempChar == 'x' || tempChar == '\n')
					{
						try
						{
							if (tempChar == 'x')
								spawnX = std::stoi(value);
							else
								spawnY = std::stoi(value);
						}
						catch (std::exception e)
						{
							// Bad number
							return -1;
						}

						value.clear();
					}
					else
					{
						if (checkCharNum(tempChar))
						{
							value += tempChar;
						}
					}
				} while (file.peek() != '@' && file.peek() != EOF);

				if (file.peek() == EOF)
					raw.push_back(std::stoi(value));
			}
			else if (!property.compare("MAP"))
			{
				raw.reserve(size.x * size.y);
				do
				{
					file.get(tempChar);
					if (tempChar == ',' || tempChar == '\n')
					{
						if (value.length() > 0)
						{
							raw.push_back(std::stoi(value));
							value.clear();
						}
					}
					else
					{
						if (checkCharNum(tempChar))
							value += tempChar;
					}
				} while (file.peek() != '@' && file.peek() != EOF);

				if (file.peek() == EOF)
					raw.push_back(std::stoi(value));
			}
			else
			{
				// Invalid property
				return -3;
			}

			property.clear();
			value.clear();
		}
		else
		{
			// Bad file format
			return -3;
		}
	}

	return 0;
}

int Level::load(const std::vector<int>&)
{
	// Not implemented
	return -2;
}

void Level::update()
{

}

void Level::draw()
{
	// Map columns (x), ros (y), and size (s)
	int mapX = 8, mapY = 8;
	int mapS = 64;
	int xo, yo;
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (raw[col * mapX + row] == 1)
			{
				glColor3f(1, 1, 1);
			}
			else
			{
				glColor3f(0, 0, 0);
			}

			xo = row * mapS;
			yo = col * mapS;
			glBegin(GL_QUADS);
			glVertex2i(xo + 1, yo + 1);
			glVertex2i(xo + 1, yo + mapS - 1);
			glVertex2i(xo + mapS - 1, yo + mapS - 1);
			glVertex2i(xo + mapS - 1, yo + 1);
			glEnd();
		}
	}
}

bool checkCharNum(char c)
{
	return (c >= 48 && c <= 57); // ASCII (Decimal) for 0 - 9
}
