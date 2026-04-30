#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "wall.hpp"

using std::ifstream;
using std::vector;
//using std::getline;

class Map
{
	private:
		ifstream mapfilestream;
		Vector2 currentpos;
		vector<Wall*> walls;
		void cycleTile();
		void place(char tileType);
		void translateLine(string mapRow);
		
	public:
		Map(ifstream mapfile)
		{
			int i = 0;
				string lineofMap;
				while (mapfile) {
					//translateLine(getline(mapfile,));
					//getline("map1.tnkm", lineofMap[10]);
				}
				currentpos.y + WALL_SIZE;
		};// makes the map and initializes the 
		~Map() = default;// destructor.
		
};
