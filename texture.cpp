#include "texture.h"
#include <kgfw/GLUtils.h>  // Include GLUtils for checkGLError

Texture::Texture( const int width, const int height, int nrChannels, const GLubyte* data)
	: Object(__FUNCTION__) {
	//TODO: Add implementation
	m_textureId = 0;

	/*glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	// Create texture
	glGenTextures(1, &m_textureId);
	checkGLError();
	// Bind it for use
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	checkGLError();
	// This needs to be called because on some cases the texture data has some different row alignment. For more info see: https://www.khronos.org/opengl/wiki/Pixel_Transfer#Pixel_layout
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if (nrChannels == 4) {
		// set the texture data as RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		checkGLError();
	}
	if (nrChannels == 3)
	{
		// set the texture data as RGB
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		checkGLError();
	}
	
	// set the texture wrapping options to repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	checkGLError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	checkGLError();
	// set the texture filtering to nearest (disabled filtering)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	checkGLError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	checkGLError();

	
}

Texture::~Texture() {
	glDeleteTextures(1, &m_textureId);
}

GLuint Texture::getTextureId() const {
	return  m_textureId;
}
