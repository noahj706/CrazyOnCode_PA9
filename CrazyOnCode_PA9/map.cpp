#include "map.hpp"

using std::getline;

void Map::cycleTile()
{
	currentpos.x + WALL_SIZE;
}
void Map::place(char wallChar)
{
	if (wallChar == 'X') {
		new Wall(currentpos);
		walls.push_back(new Wall(currentpos));
	}
	cycleTile();
}

void Map::translateLine(string mapRow)
{
	for (int i = 0; mapRow[i] = nullptr || mapRow[i] != '/n'; i++)
	{
		place(mapRow[i]);
		i++;
	}
}

Map::Map(FILE* mapfile)
{

	ifstream mapStream(mapfile);
	int i = 0;
	string mapLine;
	while (getline(mapStream, mapLine)) {
		
		translateLine(mapLine);
	}
	currentpos.y + WALL_SIZE;
}