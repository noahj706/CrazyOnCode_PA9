//primary programmer: Noah Julius
#include "bullet.hpp"
#include <vector>
#include <iostream>

Bullet::Bullet(const Vector2& position, const float& angle, const float& speed
, const float& radius, unsigned int bounces)//constructor
	: CircleEntity(position, angle, speed, radius), 
	bounces(bounces), active(true), offTimer(OFFTIMER), bounceImmunityTimer(0.0f),
	spriteSourceRectangle({ 0.0f, 0.0f, 16.0f, 16.0f })
{
	//load in sprite
	spritesheet = LoadTexture("Sprites/bullet.png");
};

bool Bullet::checkTimer()//returns true if timer is up
{
	return offTimer <= 0.0f;
}

void Bullet::update() 
{
	if (active)
	{
		if (offTimer > 0.0f) 
		{
			offTimer -= GetFrameTime();
		}
		if (bounceImmunityTimer > 0)
		{
			bounceImmunityTimer -= GetFrameTime();
		}
		moveForward();
		
	}
}
void Bullet::draw() 
{
	if (active)
	{
		DrawTexturePro(spritesheet, spriteSourceRectangle,
			{ getCenter().x , getCenter().y, 2 * getRadius(),2 * getRadius() }, { getRadius(),getRadius() }, angle, WHITE);
	}
}
void Bullet::bulletHitBulletAct()//bullet also disappears, but dif name for intuitive code reasons
{
	active = false;;
}
void Bullet::bulletHitPlayerAct()//doesnt collide unless offTimer expires to avoid shooter collision
{
	active = false;
}
void Bullet::bulletHitHorzWallAct()//bullet will bounce or deactivate
{
	if (bounces > 0)
	{
		if (bounceImmunityTimer > 0)
		{
			return; // ignore if recently bounced
		}
		angle = 360.0f - angle;//reflects angle vertically
		--bounces;
		bounceImmunityTimer = BOUNCECOOLDOWN;//start bounce cooldown
	}
	else
	{
		active = false;
	}
}
void Bullet::bulletHitVertWallAct()//bullet will bounce or deactivate
{	
	if (bounces > 0)
	{
		if (bounceImmunityTimer > 0)
		{
			return; // ignore if recently bounced
		}
		angle = 180.0f - angle;//reflects angle horizontally
		--bounces;
		bounceImmunityTimer = BOUNCECOOLDOWN;//start bounce cooldown
	}
	else
	{
		active = false;
	}
}





using std::vector;

/*
void testBullet()
{
	// Define constant screen variables
	const int screenWidth = 800;
	const int screenHeight = 450;
	const Vector2 screenCenter = { screenWidth / 2,screenHeight / 2 };

	// Initialization
	InitWindow(screenWidth, screenHeight, "Bullet Test");
	SetTargetFPS(60);

	vector<Bullet*> bList;

	// Gameplay Loop
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		
		if (IsKeyPressed('F'))
		{
			bList.push_back(new Bullet(screenCenter, 45));
			std::cout << "SHOOT!!" << std::endl;
		}
		if (IsKeyPressed(' '))
		{
			if (bList.back()->bulletHitHorzWallAct())
			{
				delete bList.back();
				bList.pop_back();
			}
			std::cout << "BOING!!!" << std::endl;
		}
		if (IsKeyPressed('M'))
		{
			if (bList.back()->bulletHitVertWallAct())
			{
				delete bList.back();
				bList.pop_back();
			}
			std::cout << "BOING!!!" << std::endl;
		}

		for (int i = 0; i < bList.size(); ++i)
		{
			bList[i]->update();
		}
		for (int i = 0; i < bList.size(); ++i)
		{
			bList[i]->draw();
		}

		EndDrawing();

	}

	CloseWindow();
}
*/