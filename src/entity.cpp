#include "entity.hpp"

void Drawable::Draw()
{
	if (m_posVBO) {
		glBindBuffer(GL_ARRAY_BUFFER, m_posVBO);
		glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
	}
}

void Drawable::Upload()
{
	if (m_vertices.size() > 0) {
		glGenBuffers(1, &m_posVBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_posVBO);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(m_vertices[0]), m_vertices.data(), GL_STATIC_DRAW);
	} else {
		fprintf(stderr, "Warning! Attempt to upload empty vertex data\n");
	}
}

Drawable::Drawable()
{
	m_posVBO = 0;
	m_position = vec3(0);
}

Drawable::~Drawable()
{
	if (m_posVBO != 0)
		glDeleteBuffers(1, &m_posVBO);
}


void Player::MoveForward(float distance, vec3 moveAxis)
{
	vec3 newPos = m_position;

	float lx = cos(m_yaw);
	float ly = 0;
	float lz = sin(m_yaw);

	if (moveAxis.y) {
		ly = sin(m_pitch);
		if (moveAxis.x || moveAxis.z) {
			lx *= cos(m_pitch);
			lz *= cos(m_pitch);
		} else {
			ly = 1;
		}
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

void Player::Update(float dt)
{
	if (glfwGetKey('W')) {
		MoveForward(10*dt, vec3(1));
	}
	if (glfwGetKey('S')) {
		MoveForward(-10*dt, vec3(1));
	}

	if (glfwGetKey('A')) {
		Strafe(-10*dt, vec3(1));
	}
	if (glfwGetKey('D')) {
		Strafe(10*dt, vec3(1));
	}

	if (glfwGetKey(GLFW_KEY_SPACE)) {
		MoveForward(10*dt, vec3(0, 1, 0));
	}
	if (glfwGetKey(GLFW_KEY_LCTRL)) {
		MoveForward(-10*dt, vec3(0, 1, 0));
	}


	int mouseDeltaX, mouseDeltaY;
	// todo
	GetMouseDeltas(800, 600, 1.f, mouseDeltaX, mouseDeltaY);

	if (mouseDeltaX || mouseDeltaY) {
		Rotate(7.f*mouseDeltaY* dt, 7.f*mouseDeltaX* dt);	
	}
}