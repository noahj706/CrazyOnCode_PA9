#include "map.hpp"

using std::getline;

void Map::cycleTile()
{
	currentPos.x += WALL_SIZE;
}
void Map::place(char tileType)
{
	if (tileType == 'X')
	{
		walls.push_back(new Wall(currentPos));
	}
	if (tileType == '1')
	{
		spawn1Pos = currentPos;
	}
	if (tileType == '2')
	{
		spawn2Pos = currentPos;
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

Map::Map()
	: currentPos({ 0, 0 }) {}

void Map::loadMap(string mapFile)
{
	currentPos = { 0, 68 };
	ifstream mapStream(mapFile);
	string mapLine;
	string buffer;
	while (getline(mapStream, buffer)) 
	{
		mapLine = buffer;
		translateLine(mapLine);
		currentPos.x = 0;
		currentPos.y += WALL_SIZE;
	}
}
void Map::unloadMap()//clears currently loaded map stuff
{
	walls.clear();
}

void Map::draw()
{
	for (Wall* pCur : walls)
	{
		pCur->draw();
	}
}

vector<Wall*>& Map::getWalls()
{
	return walls;
}
Vector2& Map::getSpawn1()
{
	return spawn1Pos;
}
Vector2& Map::getSpawn2()
{
	return spawn2Pos;
}