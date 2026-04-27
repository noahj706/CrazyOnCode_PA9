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

// ------- CLASS DEFINITION -------

class Player : public Entity
{
public:
	// Player constructor
	Player(const Vector2& position = { 0,0 }, const float& angle = 0, const float& speed = 0, const unsigned& id = 0);

	// Player destructor, use the default destructor
	~Player() = default;

	// Updates the player's position based on key presses.
	void update(void) override;

	// Draws the player on the screen.
	void draw(void) override;

	// ------- ACCESSOR MUTATOR METHODS -------

	// Returns the ID number of the player.
	unsigned getId(void) const;

	// Returns the player's current score.
	unsigned getScore(void) const;

	// ------- MUTATOR METHODS -------

	// Resets the player's score to zero.
	void resetScore(void);

	// Scores one point for a player.
	void scorePoint(void);

	// ------- CONTROLS -------

	// Fires out a bullet in the player's current direction.
	void fire(void);

	// ------- COLLISIONS -------

	// Checks for a collision with another player
	bool collidingWith(const Player& player) const;

	// ------- TEST FUNCTIONS -------

	// Player test function
	static void testPlayer(void);

private:
	// ------- ACCESSIBLE DATA ATTRIBUTES -------
	unsigned id;
	unsigned score;

	// ------- MOVEMENT ATTRIBUTES ------
	float baseSpeed;
	float turningRate;
	unsigned fireCooldownTime;
	unsigned fireCooldownTimer;

	// ------- VISUAL ATTRIBUTES -------
	Rectangle body;
	Rectangle cannon;
	unsigned barrelLength;
	Color color;
};