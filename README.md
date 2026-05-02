# **CrazyOnCode Development Team - PA9, "Atari Combat + Wii Tanks Love Child"**

**------------------------------------------------------------**

## **Program Instructions:**

In the game, you and an opponent play as toy tanks. Player 1 controls the red tank, using W to move
forward, S to move backward, A to turn counterclockwise, D to turn clockwise, and F to fire a bullet.
Player 2 controls the blue tank using the up key to move forward, the down key to move backward, the
left key to turn counterclockwise, the right key to turn clockwise, and the right control key to fire
a bullet. 

The object of each round is to maneuver around the objects scattered across the map and shoot 
the opposing player's tank. Once a tank has been shot, it will explode, and the other player will
score a point. After a player has scored, the round will end and a new one will begin. Be careful 
where you fire! Your own bullets can harm you, too.

The first player to score 5 points is the winner!

## **Design**

This program written in C++ primarily uses the basic OOP principles to operate.

All on screen game objects inherit from the Entity base class which tracks object position and movement methods.

Level information such as wall locations are stored in custom .tnkm files, which contain the level title, theme, and layout.
Such files are then loaded into place by the Map container class, filled with Wall objects that behave as the in-game walls.

All other objects including players, bullets, buttons, scoreboard, and the map are stored and managed in the GameManager container class,
since this class has oversight over all objects it controls all inter-object events such as collisions, player death calls, level load calls, etc.

## **Members and Constributions**

__Noah Julius - Lab Section 07__

-General project structure (inheritance design and program workflow)
-GameManager class (wrapper that handles inter-object interactions)
-Entity abstract class
-RectangleEntity and CircleEntity classes 
-Bullet class
-Button class

__Walker Raubuch - Lab Section 11__

-Player object class (including controls and sprite management/animation)
-Wall and Player sprites
-this readme.txt file

__Angelo Reyes - Lab Section 06__

-Scoreboard class
-Theme management (assigning proper sprites to objects)
-Sfx management (assigning sounds to event)
-Sound files (created with ChipTone by SFB Games)

__Lincoln Young - Lab Section 01__

-Wall class
-Map container class
-.tnkm map file reader
-.tnkm map file creation




