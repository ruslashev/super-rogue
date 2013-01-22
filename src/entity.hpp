#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "gameengine.hpp"

class Entity
{
private:
	SDL_Surface* surface;
	AABB position;
public:
	Entity(AABB pos) : position(pos) {}
	~Entity();

	void Update();
	void Draw(SDL_Surface* destination);
};

#endif