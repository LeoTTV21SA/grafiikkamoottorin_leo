#pragma once
#include <kgfw/Object.h>  // Include kgfw::Object to be used as a base class
#include <glad/gl.h>      // Include glad


class Texture : public kgfw::Object {
public:
	Texture( int width,  int height, int nrChannels, const GLubyte* data);
	~Texture();

	GLuint getTextureId() const;

private:
	GLuint m_textureId = 0;          //Texture id.
};
