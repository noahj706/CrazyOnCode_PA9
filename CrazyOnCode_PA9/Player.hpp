/*
	Developer: Walker Raubuch
	Description:
		This is the class definition for the Player object,
		which handles the player's movement and some other
		fun stuff.
*/

// ------- GUARD CODE -------
#pragma once

// ------- INCLUDE LIBRARIES -------
#include "entity.hpp"
#include "bullet.hpp"
#include <vector>

// ------- DEFINE CONSTANTS -------
#define TANK_BASE_SPEED 2.5
#define TANK_TURNING_RATE 0.04
#define TANK_FIRE_COOLDOWN 20
#define TANK_SIZE 32
#define BULLET_SPEED 20
#define BULLET_SIZE 5

// ------- DEFINE ENUMS -------

typedef enum PlayerId
{
	PLAYER_ONE = 1,PLAYER_TWO
};

// ------- CLASS DEFINITION -------

class Player : public CircleEntity
{
public:

	// ------- PLAYER CONSTRUCTOR AND DESTRUCTOR -------

	/* Creates a player with the given ID, which is either PLAYER_ONE or PLAYER_TWO */
	Player(const Vector2& position, const float& angle, const float& speed, const PlayerId& playerId)
		: CircleEntity(position,angle,speed,TANK_SIZE/2)
	{
		this->playerId = playerId;
		this->cooldownTimer = 0;
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

		this->stillFrame = { 0.0f, 0.0f, TANK_SIZE, TANK_SIZE };
		this->fireFrame = { 32.f, 0.0f, TANK_SIZE, TANK_SIZE };
		this->deathFrame = { 64.f,0.0f,TANK_SIZE,TANK_SIZE };
	}

	/* Default player destructor. */
	~Player() = default;

	// -------- ACCESSOR METHODS -------


	// Returns the player's ID to the user.
	PlayerId getId(void) const { return playerId; }

	// Enable/disable player movement
	void enablePlayerMovement(const bool& tf) { movementEnabled = tf; }


	// -------- PLAYER CONTROL METHODS --------


	// Performs these actions every frame. Checks for player inputs.
	void update(void) override
	{
		// Handle player motions
		doMovement();
		if (IsKeyDown(fireKey) && movementEnabled && cooldownTimer == 0) fire();
		else ceaseFire();

		// Update the bullets
		for (int i = 0; i < activeBullets.size(); ++i)
		{
			activeBullets[i]->update();
		}
	}


	// Draws the player and all of their bullets to the screen.
	void draw(void) override
	{
		DrawTexturePro(spritesheet, currentFrame, { getCenter().x , getCenter().y,TANK_SIZE,TANK_SIZE}, {TANK_SIZE / 2,TANK_SIZE / 2}, (float)RAD2DEG * angle, WHITE);
		for (int i = 0; i < activeBullets.size(); ++i)
		{
			activeBullets[i]->draw();
		}
	}

	// Checks collisions with the opponent and the opponent's bullets
	void checkCollisionsWith(const Player& opponent)
	{
		// Opponent body collisions
		if (collidingWith(opponent))
		{
			DrawText("OW!", 0, 0, 30, (playerId == PLAYER_ONE) ? RED : BLUE);
		}

		// Wall collisions

		// Bullet collisions
		for (int i = 0; i < opponent.activeBullets.size(); i++)
		{
			if (collidingWith(*(opponent.activeBullets[i])))
			{
				DrawText("OOF!", 0, 0, 30, (playerId == PLAYER_ONE) ? RED : BLUE);
				explode();
			}
		}
	}


	// ------- TEST FUNCTIONS -------

	// Player test function
	static void testPlayer(void)
	{
		// Define constant screen variables
		const int screenWidth = 800;
		const int screenHeight = 450;
		const Vector2 screenCenter = { .x = screenWidth / 2,.y = screenHeight / 2 };

		// Initialization
		InitWindow(screenWidth, screenHeight, "Player Test");
		SetTargetFPS(60);

		// Create player objects
		Player p1(screenCenter, 0, 5, PLAYER_ONE);
		Player p2({ 100,100 }, 0, 5, PLAYER_TWO);

		// Gameplay Loop
		while (!WindowShouldClose())
		{
			// Begin Drawing
			BeginDrawing();

			ClearBackground(RAYWHITE);

			// Perform drawing
			p1.draw();
			p2.draw();

			// Player movement
			p1.update();
			p2.update();

			// Collisions
			p1.checkCollisionsWith(p2);
			p2.checkCollisionsWith(p1);

			// End Drawing
			EndDrawing();

		}

		CloseWindow();

	}

private:

	// ------- DATA ATTRIBUTES -------

	PlayerId playerId;
	int cooldownTimer;
	bool movementEnabled;
	bool isAlive;
	std::vector<Bullet*> activeBullets;

	// Sprite Controllers
	Texture2D spritesheet;
	Rectangle stillFrame;
	Rectangle fireFrame;
	Rectangle deathFrame;
	Rectangle currentFrame;

	// Key controllers
	int forwardKey;
	int backwardKey;
	int leftKey;
	int rightKey;
	int fireKey;

	// ------- PRIVATE FUNCTIONS -------

	// Handle the player's movement
	void doMovement()
	{
		speed = movementEnabled*(TANK_BASE_SPEED * (int)IsKeyDown(forwardKey) + -1 * TANK_BASE_SPEED * (int)IsKeyDown(backwardKey));
		angle += movementEnabled*( - 1 * TANK_TURNING_RATE * (int)IsKeyDown(leftKey) + TANK_TURNING_RATE * (int)IsKeyDown(rightKey));
		moveForward();
	}

	// Fires a bullet in the player's current direction.
	void fire(void)
	{
		currentFrame = fireFrame;
		cooldownTimer = TANK_FIRE_COOLDOWN;
		activeBullets.push_back(new Bullet({ getCenter().x + 15 * cosf(angle),getCenter().y + 15 * sinf(angle)}, (float)angle, (float)BULLET_SPEED, (float)BULLET_SIZE));
	}

	// Handles code for when the player is not firing.
	void ceaseFire()
	{
		currentFrame = (isAlive ? stillFrame : deathFrame);
		if (cooldownTimer > 0) cooldownTimer--;
	}

	// Handles tank death
	void explode()
	{
		// Stop the player from moving
		this->movementEnabled = false;
		this->isAlive = false;
		
		angle = 0;
		currentFrame = deathFrame;

	}

	/* Returns true if the player is colliding with the opponent's body. */
	bool collidingWith(const Player& opponent)
	{
		return CheckCollisionCircles(getCenter(), getRadius(), opponent.getCenter(), opponent.getRadius());
	}

	/* Returns true if the player is colliding with a bullet. */
	bool collidingWith(const Bullet& bullet)
	{
		return CheckCollisionCircles(getCenter(), getRadius(), bullet.getCenter(), bullet.getRadius());
	}


};