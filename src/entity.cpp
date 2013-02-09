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

void Player::Move(float distance, vec3 moveAxis)
{
	vec3 newPos = m_position;

    float lx = cos(m_yaw)*cos(m_pitch);
    float ly = sin(m_pitch);
    float lz = sin(m_yaw)*cos(m_pitch);

	newPos += vec3(lx*distance, ly*distance, lz*distance)*moveAxis;

	SetPosition(newPos);
}

void Player::Rotate(float pitchAngle, float yawAngle)
{
	float limit = toRadians(89.9f);
	m_pitch = std::max(-limit, std::min(m_pitch-toRadians(pitchAngle), limit));

	m_yaw += toRadians(yawAngle);
}

mat4 Player::lookAtMat4()
{
	return lookAt(
		m_position,
		vec3(
			m_position.x+cos(m_yaw)*cos(m_pitch),
			m_position.y+sin(m_pitch),
			m_position.z+sin(m_yaw)*cos(m_pitch)
		),
		vec3(0, 1, 0)
	);
}