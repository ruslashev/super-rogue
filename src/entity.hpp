#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "utils.hpp"

class BaseEntity
{
public:
	// virtual bool Init() = 0;
	virtual void Update() = 0;
	virtual void Draw(SDL_Surface* destination) = 0;
};

class Entity : public BaseEntity
{
private:
	SDL_Surface* m_surface;
	AABB m_position;
public:
	~Entity();

	void Update();
	void Draw(SDL_Surface* destination);

	void FromImage(std::string filename);
	void SetPosition(AABB position) { m_position = position; }
	AABB GetPosition() { return m_position; }
};

#endif