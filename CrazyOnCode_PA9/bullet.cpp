#include "bullet.hpp"
#include <vector>
#include <iostream>

Bullet::Bullet(const Vector2& position, const float& angle, const float& speed
, const float& radius)//constructor
	: CircleEntity(position, angle, speed, radius) {};

void Bullet::update() 
{
	moveForward();
}
void Bullet::draw() 
{
	DrawCircleV(position, getRadius(), ORANGE);
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
			bList.push_back(new Bullet(screenCenter));
			std::cout << "SHOOT!!" << std::endl;
		}

		for (int i = 0; i < bList.size(); ++i)
		{
			bList[i]->update();
		}
		for (int i = 0; i < bList.size(); ++i)
		{
			//bList[i]->draw();
			bList[i]->drawBase();
		}

		EndDrawing();

	}

	CloseWindow();
}