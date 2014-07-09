#ifndef INPUT_HPP
#define INPUT_HPP

#include "world.hpp"

#include <SDL2/SDL.h>

class Command
{
public:
	virtual void execute(Player *ply) = 0;
};

class MoveUpCommand : public Command {
public:
	virtual void execute(Player *ply) { ply->moveUp(); }
};
class MoveDownCommand : public Command {
public:
	virtual void execute(Player *ply) { ply->moveDown(); }
};
class MoveLeftCommand : public Command {
public:
	virtual void execute(Player *ply) { ply->moveLeft(); }
};
class MoveRightCommand : public Command {
public:
	virtual void execute(Player *ply) { ply->moveRight(); }
};

class InputHandler
{
	Command *button_w, *button_s, *button_a, *button_d;

	MoveUpCommand    moveUp;
	MoveDownCommand  moveDown;
	MoveLeftCommand  moveLeft;
	MoveRightCommand moveRight;

	Command *getCommand(SDL_KeyboardEvent key);
public:
	void HandleInput(SDL_KeyboardEvent key, World *world);
	InputHandler();
};


#endif

