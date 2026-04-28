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

// ------- DEFINE CONSTANTS -------
#define TANK_BASE_SPEED 5
#define TANK_TURNING_RATE 0.1
#define TANK_FIRE_COOLDOWN 15

// ------- DEFINE ENUMS -------

typedef enum PlayerId
{
	PLAYER_ONE = 1,PLAYER_TWO
};

// ------- CLASS DEFINITION -------

class Player : public Entity
{
public:

	// ------- PLAYER CONSTRUCTOR AND DESTRUCTOR -------

	/* Creates a player with the given ID, which is either PLAYER_ONE or PLAYER_TWO */
	Player(const Vector2& position, const float& angle, const float& speed, const PlayerId& playerId)
		: Entity(position,angle,speed)
	{
		this->playerId = playerId;
		this->cooldownTimer = 0;

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
			this->fireKey = KEY_LEFT_CONTROL;
			this->spritesheet = LoadTexture("Sprites/p2_tank.png");
			break;
		}

		this->stillFrame = { 0.0f, 0.0f, 32.f, 32.f };
		this->fireFrame = { 32.f, 0.0f, 32.f, 32.f };
	}

	/* Default player destructor. */
	~Player() = default;

	// -------- ACCESSOR METHODS -------

	// Returns the player's ID to the user.
	PlayerId getId(void) const { return playerId; }

	// -------- PLAYER CONTROL METHODS --------

	// Performs these actions every frame. Checks for player inputs.
	void update(void) override
	{
		// Handle movement
		speed = TANK_BASE_SPEED * (int)IsKeyDown(forwardKey) + -1 * TANK_BASE_SPEED * (int)IsKeyDown(backwardKey);
		angle += -1 * TANK_TURNING_RATE * (int)IsKeyDown(leftKey) + TANK_TURNING_RATE * (int)IsKeyDown(rightKey);
		moveForward();

		// Handle firing
		if (IsKeyDown(fireKey) && cooldownTimer == 0)
		{
			currentFrame = fireFrame;
			cooldownTimer = TANK_FIRE_COOLDOWN;
			fire();
		}
		else
		{
			currentFrame = stillFrame;
			if (cooldownTimer > 0) cooldownTimer--;
		}
	}

	// Draws the player on the screen.
	void draw(void) override
	{
		DrawTexturePro(spritesheet, currentFrame, { position.x + 16 ,position.y + 16,32.f,32.f }, {16,16}, (float)180, WHITE);
	}

	// Fires a bullet in the player's current direction.
	void fire(void)
	{






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

		// Create player
		Player p1(screenCenter, 0, 5, PLAYER_ONE);
		//Player p2({ 100,100 }, 0, 5, 2);

		// https://www.raylib.com/examples/textures/loader.html?name=textures_srcrec_dstrec

		// Gameplay Loop
		while (!WindowShouldClose())
		{
			// Begin Drawing
			BeginDrawing();

			ClearBackground(RAYWHITE);

			//DrawTexturePro(tankTexture, imageSource, drawLocation, origin, (float)angle, WHITE);

			//EndDrawing();


			// Perform drawing
			p1.draw();
			//p2.draw();

			// Player movement
			p1.update();
			//p2.update();

			// End Drawing
			EndDrawing();

		}

		CloseWindow();









	}

private:

	// ------- DATA ATTRIBUTES -------

	PlayerId playerId;
	Texture2D spritesheet;
	Rectangle stillFrame;
	Rectangle fireFrame;
	Rectangle currentFrame;

	int forwardKey;
	int backwardKey;
	int leftKey;
	int rightKey;
	int fireKey;

	int cooldownTimer;

	// ------- ACCESSIBLE DATA ATTRIBUTES -------
	//unsigned id;
	//unsigned score;

	//// ------- MOVEMENT ATTRIBUTES ------
	//float baseSpeed;
	//float turningRate;
	//unsigned fireCooldownTime;
	//unsigned fireCooldownTimer;

	//// ------- VISUAL ATTRIBUTES -------
	//Rectangle body;
	//Rectangle cannon;
	//unsigned barrelLength;
	//Color color;

	//// ------- SPRITES -------
	//Image playerSprites[2];
	//Texture2D current;
};