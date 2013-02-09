#include "entity.hpp"

void Entity::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_VBO);
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
}

void Entity::Upload()
{
	glGenBuffers(1, &m_vertex_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(m_vertices[0]), m_vertices.data(), GL_STATIC_DRAW);
}

Entity::~Entity()
{
	if (m_vertex_VBO != 0)
		glDeleteBuffers(1, &m_vertex_VBO);
}


void Player::MoveForward(float distance, vec3 moveAxis)
{
	vec3 newPos = m_position;

	float lx = cos(m_yaw);
	float ly = sin(m_pitch);
	float lz = sin(m_yaw);

	if (moveAxis.y)
	{
		lx *= cos(m_pitch);
		lz *= cos(m_pitch);
	}

	newPos += vec3(lx*distance, ly*distance, lz*distance)*moveAxis;

	SetPosition(newPos);
}

void Player::Strafe(float distance, vec3 moveAxis)
{
	vec3 newPos = m_position;

	float lx = cos(m_yaw+M_PI/2);
	float lz = sin(m_yaw+M_PI/2);

	newPos += vec3(lx*distance, 0, lz*distance)*moveAxis;

	SetPosition(newPos);
}

void Player::Rotate(float pitchAngle, float yawAngle)
{
	float limit = toRadians(89.9f);
	m_pitch = std::max(-limit, std::min(m_pitch-toRadians(pitchAngle), limit));

	m_yaw += toRadians(yawAngle);

	if (m_yaw >= 2*M_PI)
		m_yaw = 0;
	if (m_yaw <= -2*M_PI)
		m_yaw = 0;
}

mat4 Player::LookAtMat4()
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