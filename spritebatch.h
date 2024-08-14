#pragma once
//#include <kgfw/Object.h>    // Include kgfw::Object to be used as a base class
//#include <kgfw/GLUtils.h>   // Include kgfw::Object to be used as a base class
#include "gameobject.h"
#include "Plane.h"
#include <vector>



class SpriteBatch : public kgfw::Object {
public:
	SpriteBatch();
	~SpriteBatch();

	void clear();
	void addSprite(const glm::mat4& modelMatrix, 
		const glm::mat4& viewMatrix = glm::mat4(1.0f), 
		const glm::mat4& projectionMatrix = glm::mat4(1.0f));

	void render(Shader* shader, GLuint textureId);
	

private:
	std::vector<glm::vec3>	m_positions;
	std::vector<glm::vec2>	m_texCoords;
	bool					m_needUpdateBuffers;
	GLuint					m_positionsVbo;	// Handle to positions VBO
	GLuint					m_texCoordsVbo;	// Handle to positions VBO
	GLuint					m_vao;			// Handle to VAO
};
