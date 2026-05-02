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
#include "common.hpp"
#include "bullet.hpp"
#include <vector>

// ------- DEFINE CONSTANTS -------
#define TANK_BASE_SPEED 5.5f
#define TANK_TURNING_RATE 3.3f
#define TANK_FIRE_COOLDOWN 40
#define TANK_SIZE 64
#define FIRE_FRAME_LENGTH 6.0f
#define TANK_EXPLOSION_FRAME_COUNT 30


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
	Player(const Vector2& position = { 0,0 }, const PlayerId& playerId = PLAYER_ONE, const float& angle = 0, int cooldownLength = TANK_FIRE_COOLDOWN, const float& speed = 0
		, const float& radius = TANK_SIZE / 2);

	/* Default player destructor. */
	~Player() = default;

	// -------- ACCESSOR METHODS -------

	// Returns the player's ID to the user.
	PlayerId getId(void) const;

	// Enable/disable player movement
	void enablePlayerMovement(const bool& tf);

	// -------- PLAYER CONTROL METHODS --------

	// Performs these actions every frame. Checks for player inputs.
	void update(void) override;

	// Draws the player and all of their bullets to the screen.
	void draw(void) override;

	//code was originally in update(), but in order to have no parameters in update(), I(Noah) moved the check to a separate function
	//shoots bullet if conditions met
	//pass in the bullet container
	template<typename T>
	void checkFiring(T& list)
	{
		if (IsKeyDown(fireKey) && cooldownTimer == 0) fire(list);
		else ceaseFire();
	}

	//collision acts - All by Noah :D
	void playerHitPlayerAct(const Vector2& otherPosition, float otherRadius);

	void playerHitBulletAct();

	void playerHitWallAct(Rectangle bounds);

	void freeze()//turns off movement
	{
		movementEnabled = false;
	}
	// ------- TEST FUNCTIONS -------
	/*
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
	*/
	
private:

	// ------- DATA ATTRIBUTES -------
	SoundManager* sounds = nullptr;

	int cooldownLength;

	PlayerId playerId;
	bool isAlive;
	bool movementEnabled;
	
	std::vector<Bullet*> activeBullets;

	//timers
	int cooldownTimer;
	int fireFrameTimer;//timer to hold the shooting sprite
	int explosionTimer;

	// Sprite Controllers
	Texture2D spritesheet;
	Rectangle stillFrame;
	Rectangle fireFrame;
	Rectangle deathFrame;
	Rectangle explodeFrame[2];
	Rectangle currentFrame;

	// Key controllers
	int forwardKey;
	int backwardKey;
	int leftKey;
	int rightKey;
	int fireKey;

	// ------- PRIVATE FUNCTIONS -------

	// Handle the player's movement
	void doMovement();

	// Fires a bullet in the player's current direction.
	//[FROM NOAH] - hey gang, Noah here making this function walker designed a general function, this 
	//will enable coders to shoot a bullet thats then saved in any container from the player- COOL!! :D
	template <typename T>
	void fire(T& list)
	{
		if (isAlive && movementEnabled)
		{
			if (sounds) sounds->playFire(); // Sound effects (Gello implmented)

			//creates a spawn position in front at the fron of the player
			Vector2 spawnPosition = { getCenter().x + (TANK_SIZE / 2) * cosf(angle * DEG2RAD),getCenter().y + (TANK_SIZE / 2) * sinf(angle * DEG2RAD) };

			currentFrame = fireFrame;
			cooldownTimer = cooldownLength;
			fireFrameTimer = FIRE_FRAME_LENGTH;
			list.push_back(new Bullet(spawnPosition, angle));
		}
	}

	// Handles code for when the player is not firing.
	void ceaseFire();

	// Handles tank death
	void explode();

};