#include "gameobject.h"
#include <glm/gtx/string_cast.hpp>  // glm::to_string



GameObject::GameObject(const char* const functionName)
	: Object(__FUNCTION__),
	m_position(0),
	m_angleInRadians(0),
	m_scale(1) {

}

GameObject::~GameObject()
{

}

void GameObject::setPosition(const glm::vec3& position)
{
	// Set component coordinates
	m_position = position;
}

void GameObject::setRotationZ(float angleInRadians)
{
	// Rotate point <1,0,0> arounf z-axis by (float angleInRadians)
	m_angleInRadians = angleInRadians;
}

void GameObject::setScaling(const glm::vec3& scale)
{
	m_scale = scale;
}

const glm::vec3& GameObject::getPosition() const
{
	return m_position;
}

float GameObject::getRotationZ() const
{
	return m_angleInRadians;
}

const glm::vec3& GameObject::getScaling() const
{
	return m_scale;
}

glm::mat4 GameObject::getModelMatrix() const 
{
	auto late(glm::translate(glm::mat4(1.0f), m_position));
    auto tate(glm::rotate(m_angleInRadians, glm::vec3(0.0f, 0.0f, 1.0f)));
    auto ale (glm::scale(glm::mat4(1.0f), m_scale));

	return late*tate*ale;
}
