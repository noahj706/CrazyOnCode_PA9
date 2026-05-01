//primary programmer: Noah Julius
#include "gameManager.hpp"

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

void GameManager::playerHitCheck(Player& player)
{
	for (Player* pCur : players)//iterates through entire player list
	{
		if (pCur != &player)//prevents self collision
		{
			if (CheckCollisionCircles(player.position, player.getRadius(), pCur->position, pCur->getRadius()))
			{
				player.playerHitPlayerAct(pCur->getCenter(), pCur->getRadius());
				pCur->playerHitPlayerAct(player.getCenter(), player.getRadius());//call on other player to ensure proper pushing or smt idk
			}
		}
	}
	for (Bullet* pCur : bullets)//iterates through entire bullet list
	{
			if (CheckCollisionCircles(player.position, player.getRadius(), pCur->position, pCur->getRadius())
				&& pCur->checkTimer())
			{
				player.playerHitBulletAct();
			}
	}
	for (Wall* pCur : currentMap.getWalls())//goes through wall list
	{
		if (CheckCollisionCircleRec(player.position, player.getRadius(), pCur->getBounds()))
		{
			player.playerHitWallAct(pCur->getBounds());
		}
	}
}
void GameManager::bulletHitCheck(Bullet& bullet)
{
	for (Player* pCur : players)//iterates through entire player list, this syntax is rly cool and I learned it just now :D
	{
		if(CheckCollisionCircles(bullet.position, bullet.getRadius(), pCur->position, pCur->getRadius())
			&& bullet.checkTimer())
		{
			bullet.bulletHitPlayerAct();
		}
	}
	for (Bullet* pCur : bullets)//iterates through entire bullet list
	{
		if (pCur != &bullet)//ensures bullet doesnt collide with itself
		{
			if (CheckCollisionCircles(bullet.position, bullet.getRadius(), pCur->position, pCur->getRadius()))
			{
				bullet.bulletHitBulletAct();
			}
		}
	}
	for(Wall* pCur : currentMap.getWalls())//goes through wall list
	{
		if (CheckCollisionCircleRec(bullet.position, bullet.getRadius(), pCur->getBounds()))
		{
			//gets closest point of wall to bullet center
			Rectangle bounds = pCur->getBounds();
			Vector2 closestPoint =
			{
				Clamp(bullet.position.x, bounds.x, bounds.x + bounds.width),
				Clamp(bullet.position.y, bounds.y, bounds.y + bounds.height)
			};


			//determines if colliding wall is horzontal or vertical to the closest point
			Vector2 distance = Vector2Subtract(bullet.position, closestPoint);

			//normalize to account for if width != height, i.e. a rectangle
			//this would otherwise be an issue since mesearing from cetner of wall, not the edge
			//thank you MATH 230 honors intro to linear algebra :D
			float normalizedX = fabsf(distance.x) / (bounds.width / 2);
			float normalizedY = fabsf(distance.y) / (bounds.height / 2);

			const float offset = 0.01f;//offset in place to hopefully fix corner clipping issues

			if (normalizedX > normalizedY + offset)
			{
				bullet.bulletHitVertWallAct();
			}
			else if (normalizedY > normalizedX + offset)
			{
				bullet.bulletHitHorzWallAct();
			}
			else //corner case, if the offset isn't enough and still ambiguous
			{
				bullet.bulletHitVertWallAct();
				bullet.bulletHitHorzWallAct();
			}
		}
	}

	
}
void GameManager::frameUpdatePlayers()//updates all players
{
	//updates all(2 for now) players
	for (Player* pCur : players)
	{
		playerHitCheck(*pCur);
		pCur->checkFiring(bullets);
		pCur->update();
	}
}
void GameManager::frameUpdateBullets()//updates all bullets, deletes "inactive" onces
{
	//iterates through bullet list
	//pCurIndex points to the node in the list, dereference to access bullet pointer
	//done this way to make deleting inactive bullets easy
	for (auto pCurIndex = bullets.begin(); pCurIndex != bullets.end();)
	{
		if (!(*pCurIndex)->active) //delete inactive bullet, move onto next in list
		{
			delete* pCurIndex;
			pCurIndex = bullets.erase(pCurIndex);
		}
		else //update bullet, move to next in list
		{
			bulletHitCheck(**pCurIndex);
			(*pCurIndex)->update();
			++pCurIndex;
		}
	}
}
void GameManager::readyMap()//picks random map file and loads it
{
	using std::ifstream;
	
	//loads list of map names for random selection
	ifstream mapListStream("listMaps.txt");
	vector<string> mapNameList;
	string buffer;

	while (getline(mapListStream, buffer))
	{
		mapNameList.push_back(buffer);
	}

	mapListStream.close();

	//selects random map and loads it
	currentMap.loadMap(mapNameList[(rand() % mapNameList.size())]);
}
void GameManager::readyScene()//clears currently loaded stuff and loads new ones
{
	//clear stuff from last match(if any)
	players.clear();
	bullets.clear();
	currentMap.unloadMap();

	//now ready new ones
	readyMap();
	players.push_back(new Player({ currentMap.getSpawn1().x + TANK_SIZE / 2,currentMap.getSpawn1().y + TANK_SIZE / 2 }, PLAYER_ONE, 0.0f));
	players.push_back(new Player({ currentMap.getSpawn2().x + TANK_SIZE / 2,currentMap.getSpawn2().y + TANK_SIZE / 2 }, PLAYER_TWO, 180.0f));
}
bool GameManager::checkRoundWin()//check if a player has won a round, true if atleast one player is dead
{
	for (Player* pCur : players)
	{
		if (!pCur->checkAlive() && !p1RoundWin && !p2RoundWin)
		{
			playGame = false;
			freeze();
			determineWinType();
		}
	}
}
void GameManager::giveScore()//determines round-winning player and gives point
{
	if (players.size() >= 2)//prevents pointing outside vector
	{
		//checks which player got hit, then adds score accordingly
		if (players[0]->checkAlive() && !(players[1]->checkAlive()))
		{
			scoreBoard.addScoreP1();
			p1RoundWin = true;
		}
		if (players[1]->checkAlive() && !(players[0]->checkAlive()))
		{
			scoreBoard.addScoreP2();
			p2RoundWin = true;
		}
	}
}
void GameManager::determineWinType()//determines whether to show round winning screen or game winning screen
{
	int gameWinner = scoreBoard.foundWinner();
	if (gameWinner)
	{
		if (gameWinner == 1)
		{
			p1GameWin = true;
		}
		else if (gameWinner == 2)
		{
			p2GameWin = true;
		}
		else//just a round win
		{
			roundWinTimer = 3.0f;
			giveScore();
		}
	}
}
void GameManager::showRoundWinner(PlayerId winner)//shows round winner text on screen
{
	//construct round win msg
	string message;
	if (winner == PLAYER_ONE)
	{
		message = "P1 ";
	}
	else
	{
		message = "P2 ";
	}
	message.append("ROUND POINT+");

	//measure text for centering on screen
	int fontSize = 250;
	int textWidth = MeasureText(message.c_str(), fontSize);

	//draw on center
	DrawText(message.c_str(), (SCREENWIDTH / 2) - (textWidth / 2), (SCREENHEIGHT / 2) - (fontSize / 2), fontSize, BLACK);
}
void GameManager::showGameWinner(PlayerId winner)//show winning player text on screen
{
	//construct round win msg
	string message;
	if (winner == PLAYER_ONE)
	{
		message = "P1 ";
	}
	else
	{
		message = "P2 ";
	}
	message.append("GAME WIN!");

	//measure text for centering on screen
	int fontSize = 300;
	int textWidth = MeasureText(message.c_str(), fontSize);

	//draw on center
	DrawText(message.c_str(), (SCREENWIDTH / 2) - (textWidth / 2), (SCREENHEIGHT / 2) - (fontSize / 2), fontSize, BLACK);
}
void GameManager::manageWinMenus()//does all the frame managements for displaying winner menus
{
	//manage timers
	if (roundWinTimer > 0)
	{
		roundWinTimer -= GetFrameTime();

		//draw round win message
		if (p1RoundWin)
		{
			showRoundWinner(PLAYER_ONE);
		}
		else if (p2RoundWin)
		{
			showRoundWinner(PLAYER_TWO);
		}

		//reset when timer ends
		if (roundWinTimer <= 0)//if timer ends, then start new round
		{
			roundWinTimer = 0;//incase was negative
			p1RoundWin = false;
			p2RoundWin = false;
			readyScene();
		}
	}
	if (p1GameWin)
	{
		showGameWinner(PLAYER_ONE);
	}
	else if (p2GameWin)
	{
		showGameWinner(PLAYER_TWO);
	}
	
}
void GameManager::freeze()//stops players and bullets from moving, for menu displaying
{
	for (Player* pCur : players)
	{
		pCur->freeze();
	}
	for (Bullet* pCur : bullets)
	{
		pCur->speed = 0;
	}
}
void GameManager::play()//initializes stuff then loops for entirety of game window being open
{
	// Gameplay Loop
	while (!WindowShouldClose())
	{
		//make window exist
		BeginDrawing();
		ClearBackground(BG_COLOR);

		//check for reset
		if (IsKeyPressed(' '))//if timer ends, then start new round
		{
			readyScene();
		}

		//frame update
		frameUpdatePlayers();
		frameUpdateBullets();
		scoreBoard.update();
		manageWinMenus();

		//draw
		drawAll(players);
		drawAll(bullets);
		drawAll(currentMap.getWalls());
		scoreBoard.draw();
		
		EndDrawing();
	}

	CloseWindow();

}

GameManager::GameManager()//constructor
	: playGame(false), roundWinTimer(0)
{
	//initial value tomfoolery
	srand(time(NULL));

	// Initial window setupization
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Atari Combat + Wii Tanks Love Child");
	SetTargetFPS(60);

	//player setup
	Vector2 spawn1 = { 300, 360 };
	Vector2 spawn2 = { 1300, 360 };

	players.push_back(new Player(spawn1, PLAYER_ONE));
	players.push_back(new Player(spawn2, PLAYER_TWO, 180.0f));

	play();
}



