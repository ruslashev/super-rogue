#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "utils.hpp"

class BaseEntity
{
protected:
	vec3 m_position;
public:
	void Update();
	void Draw();

	void SetPosition(vec3 newPos) { m_position = newPos; }
	vec3 GetPosition() { return m_position; }
};

class Entity : public BaseEntity
{
private:
	GLuint vbo;
public:
	vector<vec3> vertices;

	void Update();
	void Draw();
	void Upload();

	~Entity();
};

class Player : public BaseEntity
{
public:
	float m_pitch;
	float m_yaw;

	void Move(float distance, vec3 moveAxis);
	void Rotate(float pitchAngle, float yawAngle);

	mat4 lookAtMat4();
};

#endif