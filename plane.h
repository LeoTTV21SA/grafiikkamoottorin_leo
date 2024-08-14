#pragma once                // Include guard. For mor3e information, see: https://en.wikipedia.org/wiki/Pragma_once
#include <glad/gl.h>        // Include glad
#include "shader.h"
#include "gameobject.h"                               // Include kgfw::Object to be used as a base class




// Forward declare the shader class, include "shader.h" in cpp file.
class Shader;

class Plane : public GameObject {
public:
	Plane(float pivotX = 0.0f, float pivotY = 0.0f, float sizeX = 1.0f, float sizeY = 1.0f);
	
	~Plane();

	void render(Shader* shader, const glm::mat4& viewMatrix = glm::mat4(1.0f), const glm::mat4& projectionMatrix = glm::mat4(1.0f), int textureId = 0);

	void setColor(float r, float g, float b, float a=1.0f);

private:
	GLuint m_texCoordsVbo;    // Handle to positions VBO
	GLuint m_positionsVbo;    // Handle to positions VBO
	GLuint m_vao;             // Handle to VAO
	float color[4];           // Color array
};
