#include "entity.hpp"
#include <string>

class Scoreboard : public Entity
{
private:
	int score1;
	int score2;
	int fontSize;
	Color textColor;

public:
	Scoreboard(Vector2 pos = { 10, 10 }, int fontSize = 20) :
		Entity(pos),score1(0), score2(0), fontSize(fontSize), textColor(BLACK) 
	{
		speed = 0;
		angle = 0;
	}

	void update() override
	{} // should do nothing since scoreboard shouldn't be updated per frame unless animated

	void draw() override
	{
		DrawText("Player 1:", position.x, position.y, fontSize, textColor);
		DrawText(std::to_string(score1).c_str(), position.x + 120, position.y, fontSize, textColor);

		// Draw Player 2 should be below player 1
		DrawText("Player 2:", position.x, position.y + fontSize + 5, fontSize, textColor);
		DrawText(std::to_string(score2).c_str(), position.x + 120, position.y + fontSize + 5, fontSize, textColor);
	}
	void addScoreP1()
	{
		score1++;
	}
	void addScoreP2()
	{
		score2++;
	}

	void resetScore()
	{
		score1 = 0;
		score2 = 0;
	}
	// getters
	int getScore1() const { return score1; }
	int getScore2() const { return score2; }

	bool hasWinner(int winningScore = 15) const
	{
		return (score1 >= winningScore || score2 >= winningScore); // Default score of 15, can be set to another winning score
	}
};