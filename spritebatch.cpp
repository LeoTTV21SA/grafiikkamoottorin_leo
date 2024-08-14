#include "spritebatch.h"


SpriteBatch::SpriteBatch()
	: Object(__FUNCTION__),
	m_needUpdateBuffers(true) {

	// Create Vertex Array Object
	glGenVertexArrays(1, &m_vao);
	checkGLError();

	// Create Vertex Buffer Object
	glGenBuffers(1, &m_positionsVbo);
	checkGLError();

	// Create Texture Buffer Object
	glGenBuffers(1, &m_texCoordsVbo);
	checkGLError();
}

SpriteBatch::~SpriteBatch() {
	// Delete Vertex Buffer Object
	glDeleteBuffers(1, &m_positionsVbo);
	checkGLError();
	// Delete Texture Buffer Object
	glDeleteBuffers(1, &m_texCoordsVbo);
	checkGLError();
	// Delete Vertex Array Object
	glDeleteVertexArrays(1, &m_vao);
	checkGLError();
}

void SpriteBatch::clear() {
	m_positions.clear();
	m_texCoords.clear();

	// Set needUpdateBuffers to true because we need to ubdate the buffers after clearing the vectors
	m_needUpdateBuffers = true;
}

void SpriteBatch::addSprite(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {

	auto mvp = projectionMatrix * glm::inverse(viewMatrix) * modelMatrix;

	//float texCoords[] = {
	//	1.0f, 0.0f,    // left-bottom
	//	1.0f, 1.0f,    // right-bottom
	//	0.0f, 0.0f,    // top-right
	//	0.0f, 1.0f,    // left-bottom
	//	0.0f, 0.0f,    // top-right
	//	1.0f, 1.0f     // top-left
	//};

	// Texture coordinates  triangle 1:
	m_texCoords.push_back(glm::vec2(1.0f, 0.0f)); // left-bottom
	m_texCoords.push_back(glm::vec2(1.0f, 1.0f)); // right-bottom
	m_texCoords.push_back(glm::vec2(0.0f, 0.0f)); // top-right
	//  triangle 2:
	m_texCoords.push_back(glm::vec2(0.0f, 1.0f)); // left-bottom
	m_texCoords.push_back(glm::vec2(0.0f, 0.0f)); // top-rigth
	m_texCoords.push_back(glm::vec2(1.0f, 1.0f)); // top-left

	//float vertices[] = {
	//	// Vertices to draw a triangle 1.
	//   pivotX + sizeX * 0.5f,pivotY + sizeY * 0.5f, 0.f, // left  
	//   pivotX + sizeX * 0.5f,pivotY + sizeY * -0.5f, 0.f, // right 
	//   pivotX + sizeX * -0.5f,pivotY + sizeY * 0.5f, 0.f, // top
	//	// triangle 2:
	//   pivotX + sizeX * -0.5f,pivotY + sizeY * -0.5f, 0.f, // left  
	//   pivotX + sizeX * -0.5f,pivotY + sizeY * 0.5f, 0.f, // right 
	//   pivotX + sizeX * 0.5f,pivotY + sizeY * -0.5f, 0.f  // top
	//};

	// Vertice positions triangle 1:
	m_positions.push_back(mvp * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f)); // left
	m_positions.push_back(mvp * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f)); // rigth
	m_positions.push_back(mvp * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f)); // top
	// triangle 2:
	m_positions.push_back(mvp * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f)); // left
	m_positions.push_back(mvp * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f)); // rigth
	m_positions.push_back(mvp * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f)); // top
	m_needUpdateBuffers = true;
}

void SpriteBatch::render(Shader* shader, GLuint textureId) {

	// Only ubdate buffers if needed like in start of the program and after clearing the positions vectors
	if (m_needUpdateBuffers) {

		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then 
		// configure vertex attributes(s).
		glBindVertexArray(m_vao);
		checkGLError();

		// Set buffer data to m_vbo-object (bind buffer first and then set the data)
		glBindBuffer(GL_ARRAY_BUFFER, m_positionsVbo);
		checkGLError();

		glBufferData(GL_ARRAY_BUFFER, sizeof(m_positions[0]) *m_positions.size(), &m_positions[0], GL_STATIC_DRAW);
		checkGLError();

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		checkGLError();

		glEnableVertexAttribArray(0);
		checkGLError();

		// Set buffer data to m_texCoordsVbo-object (bind buffer first and then set the data)
		glBindBuffer(GL_ARRAY_BUFFER, m_texCoordsVbo);
		checkGLError();
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_texCoords[0]) *m_texCoords.size(), &m_texCoords[0], GL_STATIC_DRAW);
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

		// Set Update buffers to false because we just ubdated them
		m_needUpdateBuffers = false;
	}

	shader->bind();

	// Set the texture uniform, if texture exists
	if (textureId >= 0) {
		shader->setUniform("texture0", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
		checkGLError();
	}

	// Seeing as we only have a single VAO there's no need to bind it every time,
	// but we'll do so to keep things a bit more organized.
	glBindVertexArray(m_vao);
	checkGLError();

	// Draw 6 vertices as plane
	glDrawArrays(GL_TRIANGLES, 0, m_positions.size());
	checkGLError();
}