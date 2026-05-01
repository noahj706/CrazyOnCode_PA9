//Primary Programmer: Noah Juius
#pragma once

#include "bullet.hpp"
#include "Player.hpp"
#include "UI.hpp"
#include "wall.hpp"
#include "map.hpp"
#include "common.hpp"
#include "button.hpp"

#include <vector>
#include <list>



using std::vector;
using std::list;


class GameManager//this class will manage all of the other objects in the program, game loop is also contained here
{
	list<Bullet*> bullets;//linked list instead of vector for frequent deletion efficiency
	vector<Player*> players;//vector for random access efficiency (doesnt matter for 2 player but nice if expanded)
	Map currentMap;//generates all wall info for map
	Scoreboard scoreBoard;
	SoundManager soundManager; // added to handle sfx seamlessly for other classes
	Stage stage; // background manager
	bool playGame;//will freeze all other game operations if false, good for menu display
	bool gameActive;//will freeze all other game operations if false, good for menu display
	float roundWinTimer;
	bool p1RoundWin;
	bool p2RoundWin;
	bool p1GameWin;
	bool p2GameWin;
	vector<Button*> buttons;//will contain play and exit buttons
	bool closeGame; //exists to break game loop if needed
	
	//so since gameManager has oversight over all objects, it can check for collisions between objects
	//does so via a check then act process that I (Noah) came up with on my own :D
	//NOTE: since walls dont really DO anything, they dont get such functions

	//checks passed object againt every other object(including walls) in game, then calls the appropriate act functions inside object
	void playerHitCheck(Player& player);
	void bulletHitCheck(Bullet& bullet);
	
	//updates all changing objects, walls excluded bcs they dont change!
	//these cycle the entire list of respective objects, so only need on call per frame
	void frameUpdatePlayers();
	void frameUpdateBullets();
	void frameUpdateButtons();

	//draws all of a respective object onto the screen, intended to be called AFTER all updates are made
	//works with either a vector OR a std::list
	template <typename T>
	void drawAll(const T& list)
	{
		//draws all objects in list
		for (auto pCur : list)
		{
			pCur->draw();
			//pCur->drawBase();
		}
	}

	
	void readyMap();//picks random map file and loads it
	void readyScene();//clears currently loaded stuff

	void checkRoundWin();//check if a player has won a round, calls round win stuff if atleast one player is dead
	void giveScore();//determines winning player and gives point
	void determineWinType();//determines whether to show round winning screen or game winning screen

	void showRoundWinner(PlayerId winner);//shows round winner text on screen
	void showGameWinner(PlayerId winner);//show winning player text on screen

	void manageWinMenus();//does all the frame managements for displaying winner menus

	void freeze();//stops players and bullets from moving, for menu displaying
	void play();//loops for entirety of game window being open

public:

	GameManager();//constructor
	~GameManager() = default;//destrctor

	SoundManager& getSoundManager() 
	{ 
		return soundManager; 
	}
};