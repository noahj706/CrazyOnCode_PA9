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
		, const float& radius = TANK_SIZE / 2)
		: CircleEntity(position, angle, speed, radius), cooldownLength(cooldownLength)
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

		this->stillFrame = { 0.0f, 0.0f, 32, 32 };
		this->fireFrame = { 32.f, 0.0f, 32, 32 };
		this->deathFrame = { 64.f,0.0f,32, 32 };
	}
	
	void setSoundManager(SoundManager* soundMgr) { sounds = soundMgr; }

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
	}

	//code was originally in update(), but in order to have no parameters in update(), I(Noah) moved the check to a separate function
	//shoots bullet if conditions met
	//pass in the bullet container
	template<typename T>
	void checkFiring(T& list)
	{
		if (IsKeyDown(fireKey) && cooldownTimer == 0) fire(list);
		else ceaseFire();
	}

	bool checkAlive()
	{
		return isAlive;
	}

	// Draws the player and all of their bullets to the screen.
	void draw(void) override
	{
		DrawTexturePro(spritesheet, currentFrame, { getCenter().x , getCenter().y,TANK_SIZE,TANK_SIZE}, {TANK_SIZE / 2,TANK_SIZE / 2}, angle, WHITE);
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

	//collision acts - All by Noah :D
	void playerHitPlayerAct(const Vector2& otherPosition, float otherRadius)
	{
		//get vector from center to center
		Vector2 betweenie = this->position - otherPosition;
		Vector2 normalBetweenie = Vector2Normalize(betweenie);

		//push player out by overlap amount
		float overlap = Vector2Length(betweenie) - (getRadius() + otherRadius);
		this->position -= Vector2Scale(normalBetweenie, overlap);
	}
	void playerHitBulletAct()
	{
		explode();
	}
	void playerHitWallAct(Rectangle bounds)
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
	void ceaseFire()
	{
		currentFrame = (isAlive ? stillFrame : deathFrame);
		if (cooldownTimer > 0.0f) cooldownTimer -= GetFrameTime();
		if (fireFrameTimer > 0.0f)
		{
			currentFrame = fireFrame;
			fireFrameTimer -= GetFrameTime();
		}
	}

	// Handles tank death
	void explode()
	{ 
		if (sounds) sounds->playExplosion();
		// Stop the player from moving
		this->movementEnabled = false;
		this->isAlive = false;
		
		angle = 0;
		currentFrame = deathFrame;
	}


	//WALKER!!!!! I already made these functions in gameManager!!!!!!
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