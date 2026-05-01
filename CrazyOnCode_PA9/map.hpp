//Primary Programers: Lincolcn Young & Noah Julius
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
		vector<Wall*> walls;
		Vector2 currentPos;
		Vector2 spawn1Pos;
		Vector2 spawn2Pos;

		void cycleTile();
		void place(char tileType);
		void translateLine(string mapRow);
		
	public:
		Map();// constructor
		~Map() = default;// destructor.

		void loadMap(string mapFile);//reads map info from file
		void unloadMap();//clears currently loaded map stuff

		void draw();//draws all walls

		vector<Wall*>& getWalls();
		Vector2& getSpawn1();
		Vector2& getSpawn2();

		
};
