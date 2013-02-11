#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "utils.hpp"

class BaseEntity
{
protected:
	vec3 m_position;
public:
	virtual void Update() { };
	virtual void Draw() { };

	void SetPosition(vec3 newPos) { m_position = newPos; }
	vec3 GetPosition() { return m_position; }
};

class Entity : public BaseEntity
{
private:
	GLuint m_vertex_VBO;
public:
	vector<vec3> m_vertices;

	Entity() {
		static int welp = 0;
		printf("OI HAI M8 MNAMES ENTETEE #%i\n", welp++);

		m_position = vec3(0);
	};
	~Entity() {
		if (m_vertex_VBO != 0)
			glDeleteBuffers(1, &m_vertex_VBO);
	};

	void Update();
	void Draw();
	void Upload();
};

class Player : public BaseEntity
{
private:
	float m_pitch;
	float m_yaw;
public:

	void MoveForward(float distance, vec3 moveAxis);
	void Strafe(float distance, vec3 moveAxis);
	void Rotate(float pitchAngle, float yawAngle);

	float GetPitch() { return toDegrees(m_pitch); }
	float GetYaw() { return toDegrees(m_yaw); }

	mat4 LookAtMat4();
};

#endif