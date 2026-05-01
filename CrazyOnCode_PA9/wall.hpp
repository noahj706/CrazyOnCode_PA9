#pragma once
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::fstream;
#include "entity.hpp"


#define WALL_SIZE 64.0f
class Wall : public RectangleEntity
{
	private:
		Texture2D texture; // NEW texture member for stage themed wall
		bool isBorder;
	
	public:
		int drawWallDisplay();
		
		Wall(const Vector2& position = { 0,0 }, const float& angle = 0, const float& speed = 0,
			const float& width = WALL_SIZE, const float& height = WALL_SIZE);
		~Wall();
		void update() override;
		void draw() override;
		void defaultArena1();// generates the walls for the boarder

		void setBorder(bool border) 
		{ 
			isBorder = border; 
		}
		bool getBorder() const { return isBorder; }
		void setTexture(Texture2D newTexture) 
		{ 
			texture = newTexture;
		}
};