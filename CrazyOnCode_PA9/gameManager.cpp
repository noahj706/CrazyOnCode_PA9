//primary programmer: Noah Julius
#include "gameManager.hpp"
#include "common.hpp"
void GameManager::playerHitCheck(Player& player)
{

}
void GameManager::bulletHitCheck(Bullet& bullet)
{
	for (Player* pCur : players)//iterates through entire player list, this syntax is rly cool and I learned it just now :D
	{
		if(CheckCollisionCircles(bullet.position, bullet.getRadius(), pCur->position, pCur->getRadius()))
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
	for(Wall* pCur : walls)//goes through wall list
	{
		if (CheckCollisionCircleRec(bullet.position, bullet.getRadius(), pCur->getBounds()))
		{
			//determines if colliding wall is horzontal or vertical to the bullet
			Vector2 distance = Vector2Subtract(bullet.position, pCur->getCenter());

			//normalize to account for if width != height, i.e. a rectangle
			//this would otherwise be an issue since mesearing from cetner of wall, not the edge
			//thank you MATH 230 honors intro to linear algebra :D
			float normalizedX = fabsf(distance.x) / pCur->getBounds().width;
			float normalizedY = fabsf(distance.y) / pCur->getBounds().height;

			if (normalizedX > normalizedY)
			{
				bullet.bulletHitVertWallAct();
			}
			else
			{
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
	// Texture2D woodTex = drawWood(); texture stuff
	Texture2D poolTex = drawPool();

	// Gameplay Loop
	while (!WindowShouldClose())
	{
		//make window exist
		BeginDrawing();
		ClearBackground(BG_COLOR);
		// DrawTexture(woodTex, 0, 0, WHITE); texture stuff
		DrawTexture(poolTex, 0, 0, WHITE);

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
	// UnloadTexture(woodTex); texture stuff
	UnloadTexture(poolTex);
	CloseWindow();

}

GameManager::GameManager()//constructor
{
	//code below subject to change
	
	const Vector2 screenCenter = { .x = SCREENWIDTH / 2,.y = SCREENHEIGHT / 2 };

	// Initial window setupization
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Artari Combat + Wii Tanks Love Child");
	SetTargetFPS(60);

	//player setup
	Vector2 spawn1 = { 100, 250 };
	Vector2 spawn2 = { 800, 250 };

	players.push_back(new Player(spawn1, PLAYER_ONE));
	players.push_back(new Player(spawn2, PLAYER_TWO, 180.0f));
	

	//creates the default arena, code yoinked from Lincoln for now
	for (int i = 0; i < 18; i++)
	{
		walls.push_back(new Wall({ i * WALL_SIZE, 0 }));
		walls.push_back(new Wall({ i * WALL_SIZE, SCREENHEIGHT - WALL_SIZE }));
	}
	for (int i = 0; i < 10; i++)
	{
		walls.push_back(new Wall({ 0,50 + i * WALL_SIZE }));
		walls.push_back(new Wall({ SCREENWIDTH - WALL_SIZE, 50 + i * WALL_SIZE }));
	}

	play();
}



