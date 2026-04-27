#pragma once

#include "entity.hpp"

class Bullet : public Entity
{
	Bullet(Vector2 position, const float& angle, const float& speed); //constructor, just passes info down to entity

	void update() override;
	void draw() override;
};