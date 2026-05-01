//primary programmer: Noah Julius
#pragma once

#include "entity.hpp"
#define BULLETSPEED 7.0f
#define BULLETSIZE 8.0f
#define MAXBOUNCES 5
#define OFFTIMER 0.2f
#define BOUNCECOOLDOWN 0.04f
#define BULLETCOLOR {255, 50, 0, 255}

class Bullet : public CircleEntity
{
	unsigned int bounces;//when zero, ball dont bounce off wall
	float offTimer;// when > 0, cant collide with players
	float bounceImmunityTimer;//prevents double bouncing on wall seems

	//sprite stuff
	Texture2D spritesheet;
	Rectangle spriteSourceRectangle;

public:
	bool active;//when true, bullet is active and visible, initializes as true
	

	Bullet(const Vector2& position = {0,0}, const float& angle = 0, const float& speed = BULLETSPEED
	, const float& radius = BULLETSIZE, unsigned int bounces = MAXBOUNCES); //constructor, just passes info down to entity
	~Bullet() = default; //destructor

	bool checkTimer();//returns true if timer is up

	void update() override;
	void draw() override;

	void bulletHitBulletAct();//bullet also inactive
	void bulletHitPlayerAct();//bullet inactive under dif name for intuitive code reasons
	void bulletHitHorzWallAct();//bullet will bounce or deactivate
	void bulletHitVertWallAct();//same as above function
};
void testBullet();