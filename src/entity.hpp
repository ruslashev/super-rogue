#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "utils.hpp"

class BaseEntity
{
public:
	// virtual bool Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

class Entity : public BaseEntity
{
private:
	
public:
	~Entity();

	void Update();
	void Draw();
};

#endif