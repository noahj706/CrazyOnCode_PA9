//primary programmer: Noah Julius
#pragma once

#include "entity.hpp"
#define BULLETSPEED 4.5f
#define BULLETSIZE 7.0f
#define MAXBOUNCES 50

class Bullet : public CircleEntity
{
	unsigned int bounces;//when zero, ball dont bounce off wall

public:
	
	Bullet(const Vector2& position = {0,0}, const float& angle = 0, const float& speed = BULLETSPEED
	, const float& radius = BULLETSIZE, unsigned int = MAXBOUNCES); //constructor, just passes info down to entity
	~Bullet() = default; //destructor

	void update() override;
	void draw() override;

	void bulletHitPlayerAct();//bullet disappears
	bool bulletHitHorzWallAct();//bullet will bounce or disapear, returns true if bullet disapearts
	bool bulletHitVertWallAct();//same as above function
};
void testBullet();