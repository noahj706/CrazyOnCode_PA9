#pragma once

#include "bullet.hpp"
#include "Player.hpp"
#include "UI.hpp"

#include <vector>
#include <list>

using std::vector;
using std::list;

enum WhatsColliding
{
	PLAYER, BULLET, WALL
};

/*
WALKERRRR!!! implament this code into your player class when you get the chance!!! ty

	void playerHitWallAct();
	void playerHitBulletAct();

*/

class gameManager//this class will manage all of the other objects in the program, game loop is also contained here
{
	list<Bullet*> bullets;//linked list instead of vector for frequent deletion efficiency
	vector<Player*> players;//vector for random access efficiency (doesnt matter for 2 player but nice if expanded)
	//walls list go here once made
	Scoreboard scoreBoard;
	
	//so since gameManager has oversight over all objects, it can check for collisions between objects
	//does so via a check then act process that I (Noah) came up with on my own :D
	//NOTE: since walls dont really DO anything, they dont have such functions

	//checks passed object againt every other object(including walls) in game, then calls the appropriate act functions inside object
	void playerHitCheck(Player& player);
	void bulletHitCheck(Bullet& bullet);
	
	//updates all changing objects, walls excluded bcs they dont change!
	//these cycle the entire list of respective objects, so only need on call per frame
	void frameUpdatePlayers();
	void frameUpdateBullets();

	//draws all of a respective object onto the screen, intended to be called AFTER all updates are made
	//works with either a vector OR a std::list
	template <typename T>
	void drawAll(const T& list)
	{
		//draws all objects in list
		for (auto pCur : list)
		{
			pCur->draw();
		}
	}

	void gameLoop();//loops for entirety of game window being open

};