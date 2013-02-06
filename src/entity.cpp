#include "entity.hpp"

void Entity::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

void Entity::Upload()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
}

Entity::~Entity()
{
	glDeleteBuffers(1, &vbo);
}