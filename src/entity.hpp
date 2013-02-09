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
	GLuint m_vertex_VBO;
public:
	vector<vec3> m_vertices;

	void Update();
	void Draw();
	void Upload();

	~Entity();
};

class Player : public BaseEntity
{
private:
	float m_pitch;
	float m_yaw;
public:

	void Move(float distance, vec3 moveAxis);
	void Rotate(float pitchAngle, float yawAngle);

	float GetPitch() { return toDegrees(m_pitch); }
	float GetYaw() { return toDegrees(m_yaw); }

	mat4 lookAtMat4();
};

#endif