// ------- INCLUDE LIBRARIES -------
#include "player.hpp"

// ------- FUNCTION DEFINITIONS -------

// Player constructor
Player::Player(const Vector2& position, const float& angle, const float& speed, const unsigned& id) :
	Entity(position, angle, speed)
{
	// Visual stuff
	this->barrelLength = 35;
	this->body = { .x = position.x, .y = position.y, .width = 30, .height = 30  };
	this->cannon = { .x = position.x + barrelLength*cosf(angle), .y = position.y + barrelLength*sinf(angle), .width = 10, .height = 10};

	// Set the player number
	this->id = id;

	// Depending on the player, set their color
	switch (id)
	{
	// Player 1
	case 1:
		this->color = RED;
		break;
	case 2:
		this->color = BLUE;
		break;
	}

	// Movement stuff
	this->baseSpeed = 5;
	this->turningRate = 0.1;
	this->fireCooldownTime = 15;
	this->fireCooldownTimer = 0;

	// Scoring
	this->score = 0;

};

// Updates the player's position based on key presses.
void Player::update(void)
{
	// Player key presses
	bool forwardKeyDown = false;
	bool backwardKeyDown = false;
	bool turnLeftKeyDown = false;
	bool turnRightKeyDown = false;
	bool fireKeyDown = false;

	// Change the checks depending on player
	switch (id)
	{
	case 1:
		forwardKeyDown = IsKeyDown('W');
		backwardKeyDown = IsKeyDown('S');
		turnLeftKeyDown = IsKeyDown('A');
		turnRightKeyDown = IsKeyDown('D');
		fireKeyDown = IsKeyDown('F');
		break;
	case 2:
		forwardKeyDown = IsKeyDown(KEY_UP);
		backwardKeyDown = IsKeyDown(KEY_DOWN);
		turnLeftKeyDown = IsKeyDown(KEY_LEFT);
		turnRightKeyDown = IsKeyDown(KEY_RIGHT);
		fireKeyDown = IsKeyDown(KEY_RIGHT_CONTROL);
		break;
	}

	// Handle player movement
	speed = baseSpeed * (int)forwardKeyDown + -1 * baseSpeed * (int)backwardKeyDown;
	angle += -1 * turningRate * (int)turnLeftKeyDown + turningRate * (int)turnRightKeyDown;

	// Update the location of the body to match position
	body.x = position.x;
	body.y = position.y;

	// Move the player forward if possible
	moveForward();


	// Handle player firing
	if (fireKeyDown && fireCooldownTimer == 0)
	{
		// Fire a bullet
		fire();

		// Start the cooldown timer
		fireCooldownTimer = fireCooldownTime;
	}
	// Tick the fire time down
	if (fireCooldownTimer > 0) fireCooldownTimer--;


	// Handle player collisions

}

// Draws the player on the screen.
void Player::draw(void)
{
	// Draw the body
	DrawRectangle(body.x, body.y, body.width, body.height, color);

	// Draw the cannon
	DrawLine(body.x + body.width/2, position.y + body.height / 2, 
		     body.x + body.width / 2 + barrelLength * cosf(angle), body.y + body.height/2 + barrelLength * sinf(angle), color);
	DrawRectangle(body.x + body.width / 2 + barrelLength * cosf(angle) - cannon.width/2, body.y + body.width / 2 + barrelLength * sinf(angle) - cannon.height / 2,cannon.width,cannon.height,color);
}

// Returns the ID number of the player.
unsigned Player::getId(void) const { return id; }

// Returns the player's current score.
unsigned Player::getScore(void) const { return score; }

// Resets the player's score to zero.
void Player::resetScore(void) { score = 0; }

// Scores one point for a player.
void Player::scorePoint(void) { score++; }

// Fires a bullet.
void Player::fire(void)
{
	DrawText("Bang!", position.x, position.y - body.height/2,15,color);
}

// Checks for a collision with another player
bool Player::collidingWith(const Player& player) const
{
	return CheckCollisionRecs(this->body, player.body);
}

/* Test function for the player */
void Player::testPlayer(void)
{
	// Define constant screen variables
	const int screenWidth = 800;
	const int screenHeight = 450;
	const Vector2 screenCenter = { screenWidth / 2,screenHeight / 2 };

	// Initialization
	InitWindow(screenWidth, screenHeight, "Player Test");
	SetTargetFPS(60);

	// Create player
	Player p1(screenCenter, 0, 5, 1);
	Player p2({100,100}, 0, 5, 2);

	// Gameplay Loop
	while (!WindowShouldClose())
	{
		// Begin Drawing
		BeginDrawing();

		// Set the background of the level
		ClearBackground(RAYWHITE);
		
		// Perform drawing
		p1.draw();
		p2.draw();

		// Player movement
		p1.update();
		p2.update();

		// End Drawing
		EndDrawing();

	}

	CloseWindow();
}
