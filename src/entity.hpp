#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "utils.hpp"

class BaseEntity
{
protected:
	glm::vec3 position;
public:
	void Update();
	void Draw();

	void SetPosition(glm::vec3 newPos) { position = newPos; }
	glm::vec3 GetPosition() { return position; }
};

class Entity : public BaseEntity
{
private:
	GLuint vbo;
public:
	std::vector<glm::vec3> vertices;

	void Update();
	void Draw();
	void Upload();

	~Entity();
};

#endif