//primary programmer: Noah Julius
#include "bullet.hpp"
#include <vector>
#include <iostream>

Bullet::Bullet(const Vector2& position, const float& angle, const float& speed
, const float& radius, unsigned int bounces)//constructor
	: CircleEntity(position, angle, speed, radius), bounces(bounces), active(true) {};

void Bullet::update() 
{
	if (active)
	{
		moveForward();
	}
}
void Bullet::draw() 
{
	if (active)
	{
		DrawCircleV(position, getRadius(), ORANGE);
	}
}
void Bullet::bulletHitBulletAct()//bullet also disappears, but dif name for intuitive code reasons
{
	active = false;;
}
void Bullet::bulletHitPlayerAct()//bullet disappears
{
	active = false;
}
void Bullet::bulletHitHorzWallAct()//bullet will bounce or deactivate
{
	if (bounces > 0)
	{
		angle = 360.0f - angle;//reflects angle vertically
		--bounces;
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
		angle = 180.0f - angle;//reflects angle horizontally
		--bounces;
	}
	else
	{
		active = false;
	}
}





using std::vector;

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