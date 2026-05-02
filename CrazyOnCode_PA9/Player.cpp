// ------- INCLUDE LIBRARIES -------
#include "player.hpp"
#include "bullet.hpp"

// ------- FUNCTION DEFINITIONS -------

Player::Player(const Vector2& position, const PlayerId& playerId, const float& angle, int cooldownLength, const float& speed
	, const float& radius) : CircleEntity(position, angle, speed, radius), cooldownLength(cooldownLength)
{
	this->playerId = playerId;
	this->cooldownTimer = 0;
	this->explosionTimer = TANK_EXPLOSION_FRAME_COUNT;
	this->movementEnabled = true;
	this->isAlive = true;

	switch (playerId)
	{
	case PLAYER_ONE:

		this->forwardKey = 'W';
		this->backwardKey = 'S';
		this->leftKey = 'A';
		this->rightKey = 'D';
		this->fireKey = 'F';
		this->spritesheet = LoadTexture("Sprites/p1_tank.png");
		break;

	case PLAYER_TWO:

		this->forwardKey = KEY_UP;
		this->backwardKey = KEY_DOWN;
		this->leftKey = KEY_LEFT;
		this->rightKey = KEY_RIGHT;
		this->fireKey = KEY_RIGHT_CONTROL;
		this->spritesheet = LoadTexture("Sprites/p2_tank.png");
		break;
	}

	this->stillFrame = { 0.0f, 0.0f, 32, 32 };
	this->fireFrame = { 32.f, 0.0f, 32, 32 };
	this->explodeFrame[0] = {64.f,0.0f,32, 32};
	this->explodeFrame[1] = { 96.f,0.0f,32,32 };
	this->deathFrame = { 128.f,0.0f,32,32 };

	this->currentFrame = stillFrame;
}

void Player::doMovement()
{
	speed = movementEnabled * (TANK_BASE_SPEED * (int)IsKeyDown(forwardKey) + -1 * TANK_BASE_SPEED * (int)IsKeyDown(backwardKey));
	angle += movementEnabled * (-1 * TANK_TURNING_RATE * (int)IsKeyDown(leftKey) + TANK_TURNING_RATE * (int)IsKeyDown(rightKey));
	moveForward();
}

void Player::ceaseFire()
{
	currentFrame = stillFrame;
	if (cooldownTimer > 0.0f) cooldownTimer -= GetFrameTime();
	if (fireFrameTimer > 0.0f)
	{
		currentFrame = fireFrame;
		fireFrameTimer -= GetFrameTime();
	}
}

void Player::update(void)
{
	// Handle player motions
	doMovement();
	if (isAlive == false)
	{
		explode();
	}
}

void Player::draw(void)
{
	DrawTexturePro(spritesheet, currentFrame, { getCenter().x , getCenter().y,TANK_SIZE,TANK_SIZE }, { TANK_SIZE / 2,TANK_SIZE / 2 }, angle, WHITE);
}

void Player::enablePlayerMovement(const bool& tf) 
{ 
	movementEnabled = tf; 
}

void Player::setSoundManager(SoundManager* soundMgr)
{
	sounds = soundMgr;
}
PlayerId Player::getId(void) const 
{ 
	return playerId; 
}
void Player::playerHitWallAct(Rectangle bounds)
{
	// find closest point on rectangle to circle center
	Vector2 closestPoint =
	{
		Clamp(this->position.x, bounds.x, bounds.x + bounds.width),
		Clamp(this->position.y, bounds.y, bounds.y + bounds.height)
	};

	// get vector from closest point to circle center
	Vector2 betweenie = this->position - closestPoint;
	Vector2 normalBetweenie = Vector2Normalize(betweenie);

	// push player out by the overlap amount
	float overlap = Vector2Length(betweenie) - getRadius();
	this->position -= Vector2Scale(normalBetweenie, overlap);
}

// Handles tank death
void Player::explode()
{
	if (sounds && explosionTimer == TANK_EXPLOSION_FRAME_COUNT) sounds->playExplosion();
	// Stop the player from moving
	this->movementEnabled = false;
	this->isAlive = false;

	angle = 0;
	currentFrame = explodeFrame[explosionTimer % 2];

	if (explosionTimer > 0)
	{
		explosionTimer -= GetFrameTime();
	}
	else
	{
		currentFrame = deathFrame;
	}
}

void Player::playerHitBulletAct()
{
	explode();
}

void Player::freeze()  //turns off movement
{
	movementEnabled = false;
}

void Player::playerHitPlayerAct(const Vector2& otherPosition, float otherRadius)
{
	//get vector from center to center
	Vector2 betweenie = this->position - otherPosition;
	Vector2 normalBetweenie = Vector2Normalize(betweenie);

	//push player out by overlap amount
	float overlap = Vector2Length(betweenie) - (getRadius() + otherRadius);
	this->position -= Vector2Scale(normalBetweenie, overlap);
}