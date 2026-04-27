#pragma once

#include "entity.hpp"
#define BULLETSPEED 4.5f
#define BULLETSIZE 7.0f

class Bullet : public CircleEntity
{

public:
	Bullet(const Vector2& position = {0,0}, const float& angle = 0, const float& speed = BULLETSPEED
	, const float& radius = BULLETSIZE); //constructor, just passes info down to entity
	~Bullet() = default; //destructor

	void update() override;
	void draw() override;
	
};
void testBullet();