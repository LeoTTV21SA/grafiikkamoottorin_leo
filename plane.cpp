#include "plane.h"
#include "shader.h"
#include <kgfw/GLUtils.h>



Plane::Plane(float pivotX, float pivotY, float sizeX, float sizeY) 
	:GameObject(__FUNCTION__), 
	color{ 0 }
{
 float texCoords[] = {
   1.0f, 0.0f,    // left-bottom (vertice position: <-0.5,-0.5>)
   1.0f, 1.0f,    // right-bottom (vertice position: <0.5,-0.5>)
   0.0f, 0.0f,    // top-right (vertice position: <0.5,0.5>)
   0.0f, 1.0f,    // left-bottom (vertice position: <-0.5,-0.5>)
   0.0f, 0.0f,    // top-right (vertice position: <0.5,0.5>)
   1.0f, 1.0f     // top-left (vertice position: <-0.5,0.5>)
 };

    float posX = 0.5f * sizeX;
	float posY = 0.5f * sizeY;

	// Vertices to draw a triangle.
	float vertices[] = {
		 posX + pivotX,  posY + pivotY, 0.0f,  // left (0.5f *sizeX + pivotX , 0,5*sizeY + pivotY , 0.0f)
		 posX + pivotX, -posY + pivotY, 0.0f, // right (0.5f *sizeX + pivotX, -0,5*sizeY + pivotY , 0.0f)
		-posX + pivotX,  posY + pivotY, 0.0f,  // top  (-0.5f *sizeX + pivotX, 0,5*sizeY + pivotY , 0.0f)

		-posX + pivotX, -posY + pivotY, 0.0f, // left (-0.5f *sizeX + pivotX , -0,5*sizeY + pivotY , 0.0f)
		-posX + pivotX,  posY + pivotY, 0.0f, // right (-0.5f *sizeX + pivotX , 0,5*sizeY + pivotY , 0.0f) 
		 posX + pivotX, -posY + pivotY, 0.0f, // top   (0.5f *sizeX + pivotX , -0,5*sizeY + pivotY , 0.0f)
		
    };

    // Create Vertex Array Object
	glGenVertexArrays(1, &m_vao);
	checkGLError();

	//Create buffer for them
	glGenBuffers(1, &m_texCoordsVbo);
	checkGLError();
	// Create Vertex Buffer Object
	glGenBuffers(1, &m_positionsVbo);
	checkGLError();

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then 
	// configure vertex attributes(s).
	glBindVertexArray(m_vao);
	checkGLError();

	// Set buffer data to m_vbo-object (bind buffer first and then set the data)
	glBindBuffer(GL_ARRAY_BUFFER, m_positionsVbo);
	checkGLError();

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	checkGLError();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	checkGLError();
	glEnableVertexAttribArray(0);
	checkGLError();

	// Set buffer data to m_texCoordsVbo-object (bind buffer first and then set the data)
	glBindBuffer(GL_ARRAY_BUFFER, m_texCoordsVbo);
	checkGLError();
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	checkGLError();
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	checkGLError();
	glEnableVertexAttribArray(1);
	checkGLError();


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex 
	// attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	checkGLError();

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this
	// VAO, but this rarely happens. Modifying other VAOs requires a call to glBindVertexArray
	// anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	checkGLError();
}

Plane::~Plane()
{	
	// Delete Vertex Buffer Object
	glDeleteBuffers(1, &m_positionsVbo);
	checkGLError();
	// Delete Vertex Array Object
	glDeleteVertexArrays(1, &m_vao);
	checkGLError();
	// Delete Texture Buffer Object
	glDeleteBuffers(1, &m_texCoordsVbo);
	checkGLError();
}


void Plane::render(Shader* shader, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, int textureId)
{
	shader->bind();

	shader->setUniform("MVP", projectionMatrix * glm::inverse(viewMatrix) * getModelMatrix());
	checkGLError();

	shader->setUniform("color", color[0], color[1], color[2],color[3]);
	
	// Set the texture uniform, if texture exists
	if (textureId > 0) {
		shader->setUniform("texture0", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}


	// Seeing as we only have a single VAO there's no need to bind it every time,
	// but we'll do so to keep things a bit more organized.
	glBindVertexArray(m_vao);
	checkGLError();

	// Draw 6 vertices as triangles
	glDrawArrays(GL_TRIANGLES, 0, 6);
	checkGLError();
}
void Plane::setColor(float r,float g, float b , float a)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;
}