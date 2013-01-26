#include "entity.hpp"

void Entity::Update()
{

}

void Entity::Draw(SDL_Surface* destination)
{
	SDL_Rect offset;
	offset.x = m_position.x;
	offset.y = m_position.y;

	SDL_BlitSurface(m_surface, NULL, destination, &offset);
}

Entity::~Entity()
{
	if (m_surface != 0)
		SDL_FreeSurface(m_surface);
}

void Entity::FromImage(std::string filename)
{
	m_surface = loadImage(filename);
}