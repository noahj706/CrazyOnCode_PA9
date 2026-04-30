//primary programmer: Noah Julius
#include "gameManager.hpp"
#include <iostream>

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
				std::cout << "PLAYER HIT BULLET!!!" << std::endl;
				player.playerHitBulletAct();
			}
	}
	for (Wall* pCur : walls)//goes through wall list
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
		std::cout << "BULLET CHECKED!!!!" << std::endl;
		if(CheckCollisionCircles(bullet.position, bullet.getRadius(), pCur->position, pCur->getRadius())
			&& bullet.checkTimer())
		{
			std::cout << "BULLET HIT PLAYER!!!" << std::endl;
			bullet.bulletHitPlayerAct();
		}
	}
	for (Bullet* pCur : bullets)//iterates through entire bullet list
	{
		if (pCur != &bullet)//ensures bullet doesnt collide with itself
		{
			if (CheckCollisionCircles(bullet.position, bullet.getRadius(), pCur->position, pCur->getRadius()))
			{
				//bullet.bulletHitBulletAct();
			}
		}
	}
	for(Wall* pCur : walls)//goes through wall list
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

void GameManager::play()//initializes stuff then loops for entirety of game window being open
{
	// Gameplay Loop
	while (!WindowShouldClose())
	{
		//make window exist
		BeginDrawing();
		ClearBackground(BG_COLOR);

		//check for reset
		if (IsKeyPressed(' '))
		{
			Vector2 spawn1 = { 300, 360 };
			Vector2 spawn2 = { 1300, 360 };

			players.clear();
			bullets.clear();

			players.push_back(new Player(spawn1, PLAYER_ONE, 0.0f, 1));
			players.push_back(new Player(spawn2, PLAYER_TWO, 180.0f));
		}

		//frame update
		frameUpdatePlayers();
		frameUpdateBullets();

		//draw
		drawAll(players);
		drawAll(bullets);
		drawAll(walls);
		scoreBoard.draw();
		
		EndDrawing();
	}

	CloseWindow();

}

GameManager::GameManager()//constructor
{
	//code below subject to change
	
	const Vector2 screenCenter = { .x = SCREENWIDTH / 2,.y = SCREENHEIGHT / 2 };

	// Initial window setupization
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Atari Combat + Wii Tanks Love Child");
	SetTargetFPS(60);

	//player setup
	Vector2 spawn1 = { 300, 360 };
	Vector2 spawn2 = { 1300, 360 };

	players.push_back(new Player(spawn1, PLAYER_ONE));
	players.push_back(new Player(spawn2, PLAYER_TWO, 180.0f));
	

	//creates the default arena, code yoinked from Lincoln for now
	for (int i = 0; i < 32; i++)
	{
		walls.push_back(new Wall({ i * WALL_SIZE, 0 }));
		walls.push_back(new Wall({ i * WALL_SIZE, SCREENHEIGHT - WALL_SIZE }));
	}
	for (int i = 0; i < 13; i++)
	{
		walls.push_back(new Wall({ 0,50 + i * WALL_SIZE }));
		walls.push_back(new Wall({ SCREENWIDTH - WALL_SIZE, 50 + i * WALL_SIZE }));
	}

	play();
}



