#include "entity.hpp"

void Entity::updateVelocity()//basically polar to cartesian coords
{
	velocity = {speed * cosf(angle * DEG2RAD), speed * sinf(angle * DEG2RAD)};
}
Entity::Entity(const Vector2& position, const float& angle, const float& speed)//constructor
	: position(position), angle(fmodf(angle, 360.0f)), speed(speed), velocity({0,0})
{
	if (this->angle < 0)//ensures no negative angles, maintains direction
	{
		this->angle += 360.0f;
	}
}
void Entity::moveForward()//uses updateVelocity() and then adds it to position
{
	updateVelocity();
	position = Vector2Add(position, velocity);
}
void Entity::moveBackward()//subtracts vector from position as a halved rate
{
	updateVelocity();
	Vector2Scale(velocity, BACKWARD_SPEED);//backward speed adjustable in the header file
	position = Vector2Subtract(position, velocity);
}

//CircleEntity defintions
CircleEntity::CircleEntity(const Vector2& position, const float& angle, const float& speed, 
	const float& radius)//constructor
	: Entity(position, angle, speed), radius(radius) {}

Vector2 CircleEntity::getCenter()//returns a point that is centered on the circle
{
	return position;
}
const float& CircleEntity::getRadius() const//returns radius
{
	return radius;
}
void CircleEntity::drawBase()//draws a red outline of the shape
{
	DrawCircleLinesV(position, radius, RED);
}

//RectangleEntity defintions
RectangleEntity::RectangleEntity(const Vector2& position, const float& angle, const float& speed,
	const float& width, const float& height)//constructor
	: Entity(position, angle, speed), width(width), height(height) {}

Rectangle RectangleEntity::getBounds()//returns shape as raylib Rectangle type
{
	return { position.x, position.y, width, height };
}
Vector2 RectangleEntity::getCenter()//returns a point that is centered on the shape
{
	return { position.x + width, position.y - height };
}
void RectangleEntity::setPositionFromCenter(const Vector2& centerCoords)//sets position such that the rectangle is centered on passed coords
{
	position = { centerCoords.x - width, centerCoords.y + height };
}
void RectangleEntity::drawBase()//draws a red outline of the shape
{
	DrawRectangleLinesEx(getBounds(), 1.0f, RED);
}