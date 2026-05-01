#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "wall.hpp"

using std::ifstream;
using std::vector;
using std::getline;

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
		Map(string mapFile);
		~Map() = default;// destructor.
		void draw();
		
};
