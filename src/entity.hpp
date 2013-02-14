#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "utils.hpp"
#include "gameengine.hpp"

class BaseEntity
{
protected:
	vec3 m_position;
public:
	void Update(float dt);
	void Draw();

	void SetPosition(vec3 newPos) { m_position = newPos; }
	vec3 GetPosition() { return m_position; }
};

class Drawable : public BaseEntity
{
private:
	GLuint m_posVBO;
public:
	Drawable();
	~Drawable();

	void Update(float dt);
	void Draw();
	void Upload();

	vector<vec3> m_vertices;
	AABB m_collisionBox;
	mat4 modelMat;
};

class Player : public BaseEntity
{
private:
	float m_pitch;
	float m_yaw;
public:
	void Update(float dt);

	void MoveForward(float distance, vec3 moveAxis);
	void Strafe(float distance, vec3 moveAxis);
	void Rotate(float pitchAngle, float yawAngle);

	float GetPitch() { return toDegrees(m_pitch); }
	float GetYaw() { return toDegrees(m_yaw); }

	mat4 LookAtMat4();
};

#endif