//primary programmer: Noah Julius
#pragma once

#include "entity.hpp"
#define BULLETSPEED 4.5f
#define BULLETSIZE 7.0f
#define MAXBOUNCES 50
#define OFFTIMER 5.0f

class Bullet : public CircleEntity
{
	unsigned int bounces;//when zero, ball dont bounce off wall
	unsigned int offTimer;// when > 0, cant collide with players

public:
	bool active;//when true, bullet is active and visible, initializes as true

	Bullet(const Vector2& position = {0,0}, const float& angle = 0, const float& speed = BULLETSPEED
	, const float& radius = BULLETSIZE, unsigned int bounces = MAXBOUNCES); //constructor, just passes info down to entity
	~Bullet() = default; //destructor

	void update() override;
	void draw() override;

	void bulletHitBulletAct();//bullet also inactive
	void bulletHitPlayerAct();//bullet inactive under dif name for intuitive code reasons
	void bulletHitHorzWallAct();//bullet will bounce or deactivate
	void bulletHitVertWallAct();//same as above function
};
void testBullet();