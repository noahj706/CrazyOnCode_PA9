#include "entity.hpp"
//
//void Entity::updateVelocity()//basically polar to cartesian coords
//{
//	velocity = {speed * cosf(angle), speed * sinf(angle)};
//}
//Entity::Entity(Vector2 position = { 0,0 }, float angle = 0, float speed = 0)//constructor
//{
//	this->position = position;
//	this->angle = angle;
//	this->speed = speed;
//}
//
//void Entity::moveForward()//uses updateVelocity() and then adds it to position
//{
//	updateVelocity();
//	position = Vector2Add(position, velocity);
//}
//void Entity::moveBackward()//subtracts vector from position as a halved rate
//{
//	updateVelocity();
//	Vector2Scale(velocity, BACKWARD_SPEED);//backward speed adjustable in the header file
//	position = Vector2Subtract(position, velocity);
//}