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

	Entity(const Vector2& position = {0,0}, const float& angle = 0, const float& speed = 0);//constructor

	virtual ~Entity() = default;//virtual destructor

	virtual void update() = 0; //pure virtual function, different for whatever inherits
	virtual void draw() = 0; //pure virtual function, this'll be the render step for the object
	
	void moveForward();//uses updateVelocity() and then adds it to position
	void moveBackward();//subtracts vector from position as a halved rate

	
};

class CircleEntity : public Entity
{
	float radius;//public for collision checking reasons, functionally same as having a getter in place

public:
	CircleEntity(const Vector2& position = { 0,0 }, const float& angle = 0, const float& speed = 0, 
		const float& radius = 1);//constructor
	~CircleEntity() = default; //destructor

	Vector2 getCenter();//returns a point that is centered on the shape
	const float& getRadius() const;//returns radius 

	void drawBase();//draws a red outline of the shape
};

class RectangleEntity : public Entity
{
	float width;
	float height;

public:
	RectangleEntity(const Vector2& position = { 0,0 }, const float& angle = 0, const float& speed = 0,
		const float& width = 1, const float& height = 1);//constructor
	~RectangleEntity() = default; //destructor

	Rectangle getBounds();//returns shape as raylib Rectangle type
	Vector2 getCenter();//returns a point that is centered on the shape
	void setPositionFromCenter(const Vector2& centerCoords);//sets position such that the rectangle is centered on passed coords

	void drawBase();//draws a red outline of the shape
};