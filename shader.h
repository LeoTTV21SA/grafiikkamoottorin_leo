#pragma once                // Include guard. For more information, see: https://en.wikipedia.org/wiki/Pragma_once
#include <kgfw/Object.h>    // Include kgfw::Object to be used as a base class
#include <glad/gl.h>        // Include glad
#include <GLFW/glfw3.h>
#include <string>
#include "gameobject.h"
#include <glm/glm.hpp>      // Include glm

class Shader : public kgfw::Object {
public:
	//Shader Constructor
	Shader(const char* const vertexShaderString, const char* const fragmentShaderString);

	// Shader Destructor
	~Shader();

	void bind();
	void setUniform(const std::string& name, float x, float y, float z);
	void setUniform(const std::string& name, const glm::mat4& m);
	void setUniform(const std::string& name, float x, float y, float z, float w);
	void setUniform(const std::string& name, int value);
private:
	GLint m_shaderProgram;  // Handle to the shader program
	
};
