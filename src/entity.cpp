#include "entity.hpp"

void Entity::Draw(SDL_Surface* destination)
{
	SDL_Rect offset;

	offset.x = position.x;
	offset.y = position.y;

	SDL_BlitSurface(surface, NULL, destination, &offset);
}

Entity::~Entity()
{
	SDL_FreeSurface(surface);
}