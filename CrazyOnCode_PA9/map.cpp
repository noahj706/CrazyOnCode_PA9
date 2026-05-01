#include "map.hpp"

using std::getline;

void Map::cycleTile()
{
	currentpos.x += WALL_SIZE;
}
void Map::place(char wallChar)
{
	if (wallChar == 'X') {
		walls.push_back(new Wall(currentpos));
	}
	cycleTile();
}

void Map::translateLine(string mapRow)
{
	for (char c : mapRow)
	{
		place(c);
	}
}

Map::Map(string mapFile)
	: currentpos({ 0,68 })
{
	ifstream mapStream(mapFile);
	string mapLine;
	string buffer;
	while (getline(mapStream, buffer)) {
		mapLine = buffer;
		translateLine(mapLine);
		currentpos.x = 0;
		currentpos.y += WALL_SIZE;
	}
	
}
void Map::draw()
{
	for (Wall* pCur : walls)
	{
		pCur->draw();
	}
}