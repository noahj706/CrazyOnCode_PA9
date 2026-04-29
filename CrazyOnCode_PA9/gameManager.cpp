//primary programmer: Noah Julius
#include "gameManager.hpp"

void gameManager::playerHitCheck(Player& player)
{

}
void gameManager::bulletHitCheck(Bullet& bullet)
{
	for (Player* pCur : players)//iterates through entire player list, this syntax is rly cool and I learned it just now :D
	{
		//if(CheckCollisionCircles(bullet.position, bullet.getRadius(), pCur->position, pCur->getRadius()))
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
	//for(Wall* pCur : walls)
	{
		//if (CheckCollisionCircleRec(bullet.position, bullet.getRadius(), pCur->getBounds())
		{
			//determines if colliding wall is horzontal or vertical to the bullet
			Vector2 distance = Vector2Subtract(bullet.position, pCur->getCenter());

			//normalize to account for if width != height, i.e. a rectangle
			//this would otherwise be an issue since mesearing from cetner of wall, not the edge
			//thank you MATH 230 honors intro to linear algebra :D
			float normalizedX = fabsf(distance.x) / pCur->getCenter().width;
			float normalizedY = fabsf(distance.y) / pCur->getCenter().height;

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

void gameManager::frameUpdatePlayers()//updates all players
{
	//updates all(2 for now) players
	for (Player* pCur : players)
	{
			pCur->update();
	}
}
void gameManager::frameUpdateBullets()//updates all bullets, deletes "inactive" onces
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
			(*pCurIndex)->update();
			++pCurIndex;
		}
	}
}


