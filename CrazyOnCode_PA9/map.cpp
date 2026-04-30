#include "map.hpp"
void Map::cycleTile()
{
	currentpos.x + WALL_SIZE;
}
void Map::place(char wallChar=' ')
{
	if (wallChar == 'X') {
		//new Wall->position(currentpos.x + WALL_SIZE);
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

//Map::Map(ifstream mapfile)
//{
//	int i = 0;
//	string lineofMap;
//	while (mapfile) {
//		//translateLine(getline(mapfile,));
//		getline( "map1.tnkm", lineofMap);
//	}
//	currentpos.y + WALL_SIZE;
//}