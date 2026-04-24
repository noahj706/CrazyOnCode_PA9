#pragma once

#include "raylib.h"
#include "raymath.h"

#define BACKWARD_SPEED 0.5 //how much % slower smth moves backwards

class Entity
{
	Vector2 velocity; //combines angle and speed into a single vector, this is then added to position for movement
	void updateVelocity();//basically polar to cartesian coords

public:		
	Vector2 position;
	float angle; //will be stored as deg, getters can pass as deg or radians with DEG2RAD from raylib
	float speed; //distance added to position for movement

	Entity(Vector2 position = {0,0}, float angle = 0, float speed = 0);//constructor

	virtual ~Entity() = default;//virtual destructor

	virtual void update() = 0; //pure virtual function, different for whatever inherits
	virtual void draw() = 0; //pure virtual function, this'll be the render step for the object
	
	void moveForward();//uses updateVelocity() and then adds it to position
	void moveBackward();//subtracts vector from position as a halved rate
};