#include "bullet.hpp"

Bullet::Bullet(Vector2 position, const float& angle, const float& speed)//constructor calling entity constructor
	: Entity(position, angle, speed) {};

void Bullet::update() 
{
	moveForward();
	//insert codeblock for collision to delete bullet when occurs
	//
	//
	//
}
void Bullet::draw() 
{
	DrawCircleV(position, 5.0f, ORANGE);
}