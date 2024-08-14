#include <stdio.h>			// Include stdio.h, which contains printf-function
#include <kgfw/Object.h>	// Include kgfw::Object
#include <glad/gl.h>		// Include glad
#include <GLFW/glfw3.h>		// Include glfw
#include <kgfw/GLUtils.h>
#include "texture.h"
#include "plane.h"
#include <vector>
#include <iostream>
#include "camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "gameobject.h"
#include <algorithm>
#include "spritebatch.h"
#include "player.h"

#include <map>

class Application : public GameObject
{
	Player* player;

public:
	Application() : GameObject(__FUNCTION__), m_shader(0) {

		const char* vertexShaderSource =
			// specify which version of GLSL should be used to compile/link a shader. This example uses version 3.3.
			"#version 330 core\n"
			// Specify that in location 0 are positions of the primitive.
			"layout (location = 0) in vec3 position;\n"

			// Texture coordinate of the vertex at location 1
			"layout (location = 1) in vec2 texCoordi;\n"
			/*"uniform mat4 MVP;\n"*/

			// Vertex shader main function.
			  // Outgoing texture coordinate
			"out vec2 texCoord;"
			"void main()\n"
			"{\n"

			"   texCoord = texCoordi;\n"
			"   gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
			"}";
			// Write position to gl_Position output variable.
			 // Pass texture coordinate to the fragment shader
			/*"   texCoord = texCoordi;\n"
			"   gl_Position = MVP * vec4(position.x, position.y, position.z, 1.0);\n"
			"}";*/


		const char* fragmentShaderSource =
			// specify which version of GLSL should be used to compile/link a shader. This example uses version 3.3.
			"#version 330 core\n"
			/*"uniform vec4 color;\n"*/

			// Incoming texture id
			"uniform sampler2D texture0;\n"
			// Incoming texture coordinate
			"in vec2 texCoord;"

			// Declare fragment shader output
			"out vec4 FragColor;\n"
			// Fragment shader main function.
			"void main()\n"
			"{\n"

			// Fetch pixel color using texture2d-function.
			"   FragColor = texture2D(texture0, texCoord);\n"
			//"   FragColor =vec4(texCoord.x * texCoord.y,0.0,0.0,1.0);\n"
			"}";

		// The data for our texture (2x2 4 bytes per pixel bitmap)
		const int width = 2;
		const int height = 2;
		GLubyte data[height * width * 4] = {
			// Red, green, blue and alpha
			0xff, 0x0A, 0x0A, 0xff,    // Red"ish"-color
			0x0A, 0xff, 0x0A, 0xff,    // Green"ish"-color
			0x0A, 0x0A, 0xff, 0xff,    // Blue"ish"-color
			0xff, 0xff, 0x0A, 0xff     // Yellow"ish"-color
		};
		m_spriteBatch = new SpriteBatch();
		m_playerSpriteBatch = new SpriteBatch();
		
		int x, y, n;
		unsigned char* data1 = stbi_load("fotos/kamk-logo.png", &x, &y, &n, 0);
		kamk = new Texture(y, x, n, data1);
		unsigned char* data3 = stbi_load("fotos/tiki.png", &x, &y, &n, 0);
		tiki = new Texture(y, x, n, data3);
		unsigned char* data4 = stbi_load("fotos/helado.png", &x, &y, &n, 0);
		helado = new Texture(y, x, n, data4);
		// use your data
		m_textures.push_back(kamk);
		
		m_textures.push_back(helado);
		m_textures.push_back(tiki);

		stbi_image_free(data1);
		stbi_image_free(data3);
		stbi_image_free(data4);

		// Create ortho-projective camera with screen size 640x480
		m_camera = new Camera(-0.5f * 640.0f, 640.0f * 0.5f, -0.5f * 480.0f, 0.5f * 480.0f);
		//
		

		// Set camera transform (view transform)
		m_camera->setPosition(glm::vec3(-10.0f, -10.0f, 0.0f));

		// Build and compile our shader program
		m_shader = new Shader(vertexShaderSource, fragmentShaderSource);

		GameObject* a = new GameObject("");
		a->setScaling(glm::vec3(100, 100, 0));
		a->setPosition(glm::vec3(200, -90, 0));

		GameObject* b = new GameObject("");
		b->setScaling(glm::vec3(100, 100, 0));
		b->setPosition(glm::vec3(150, 100, 0));

		GameObject* c = new GameObject("");
		c->setScaling(glm::vec3(100, 100, 0));
		c->setPosition(glm::vec3(100, -70, 0));

		Player* d = new Player();
		d->setScaling(glm::vec3(100, 100, 0));
		d->setPosition(glm::vec3(50, 50, 0));

		GameObject* e = new GameObject("");
		e->setScaling(glm::vec3(100, 100, 0));
		e->setPosition(glm::vec3(0, 0, 0));

		GameObject* f = new GameObject("");
	    f->setScaling(glm::vec3(100, 100, 0));
		f->setPosition(glm::vec3(-50, 50, 0));

		GameObject* g = new GameObject("");
		g->setScaling(glm::vec3(100, 100, 0));
		g->setPosition(glm::vec3(-100, -50, 0));

		GameObject* h = new GameObject("");
		h->setScaling(glm::vec3(100, 100, 0));
		h->setPosition(glm::vec3(-150, 100, 0));

		GameObject* i = new GameObject("");
		i->setScaling(glm::vec3(100, 100, 0));
		i->setPosition(glm::vec3(-200, -100, 0));

		GameObject* j = new GameObject("");
		j->setScaling(glm::vec3(100, 100, 0));
		j->setPosition(glm::vec3(-250, -100, 0));

		player = d;

		m_gameobjects.emplace(tiki, a);
		m_gameobjects.emplace(tiki, b);
		m_gameobjects.emplace(helado, c);
		m_gameobjects.emplace(helado, d);
		m_gameobjects.emplace(helado, e);
		m_gameobjects.emplace(tiki, f);
		m_gameobjects.emplace(kamk, g);
		m_gameobjects.emplace(kamk, h);
		m_gameobjects.emplace(kamk, i);
		m_gameobjects.emplace(kamk, j);
	}

		
		

	~Application() {
		// Delete shader
		delete m_shader;
		m_shader = 0;

		// Delete camera
		delete m_camera;
		m_camera = 0;

		// Delete texture;
		delete helado;
		helado = 0;
		delete tiki;
		tiki = 0;
		delete kamk;
		kamk = 0;


		// Delete spriteBatch
		delete m_spriteBatch;
		m_spriteBatch = 0;

		// Delete gameObjects
		/*
		for (auto it : m_gameObjects) {
			delete it;
		}*/

		//for (auto plane : m_planes) {
		//	delete plane;
		//}
		/*for (auto Alpha : m_planesAlpha) {
			delete Alpha;
		}*/
	}


	void render(GLFWwindow* window) {
		// Query the size of the framebuffer (window content) from glfw.
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		// Setup the opengl wiewport (i.e specify area to draw)
		glViewport(0, 0, width, height);
		checkGLError();

		// Set color to be used when clearing the screen
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		checkGLError();

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);
		checkGLError();

		for (std::multimap<Texture*, GameObject*>::iterator itr = m_gameobjects.begin(); itr != m_gameobjects.end(); ) {
			/* ... process *itr ... */

			/* Now, go skip to the first entry with a new key. */
			std::multimap<Texture*, GameObject*>::iterator curr = itr;
			while (itr != m_gameobjects.end() && itr->first == curr->first)
			{
				m_playerSpriteBatch->clear();

				m_playerSpriteBatch->addSprite(itr->second->getModelMatrix(), m_camera->getModelMatrix(), m_camera->getProjectionMatrix());

				m_playerSpriteBatch->render(m_shader, itr->first->getTextureId());

				++itr;
			}
			
		}

		// Delete gameObjects

		/*m_spriteBatch->clear();
		m_spriteBatch->addSprite(m_gameObjects[0]->getModelMatrix(), m_camera->getModelMatrix(), m_camera->getProjectionMatrix());
		m_spriteBatch->addSprite(m_gameObjects[1]->getModelMatrix(), m_camera->getModelMatrix(), m_camera->getProjectionMatrix());
		m_spriteBatch->addSprite(m_gameObjects[2]->getModelMatrix(), m_camera->getModelMatrix(), m_camera->getProjectionMatrix());
		m_spriteBatch->render(m_shader, mansikka->getTextureId());*/

		/*for (auto it : m_gameObjects)
		{


			m_spriteBatch->render(m_shader, mansikka->getTextureId());

			m_spriteBatch->render(m_shader, helado->getTextureId());
			m_spriteBatch->render(m_shader, kamk->getTextureId());
			m_spriteBatch->render(m_shader, tiki->getTextureId());
		}*/

		//m_spriteBatch->render(m_shader, mansikka->getTextureId());


		//Sort The planesAlpha by depth (ascending order, wher the smallest z is first to render)

		/*std::sort(m_planesAlpha.begin(), m_planesAlpha.end(), [](Plane* lhs, Plane* rhs)->bool {
			return lhs->getPosition().z < rhs->getPosition().z;
			});*/

		//Sort The planes by depth (ascending order, wher the smallest z is first to render)

		//std::sort(m_planes.begin(), m_planes.end(), [](Plane* lhs, Plane* rhs)->bool {
		//	return lhs->getPosition().z < rhs->getPosition().z;
		//	});

		//
		//// draw planes
		//for (auto plane : m_planes) {
		//	plane->render(m_shader, m_camera->getModelMatrix(), m_camera->getProjectionMatrix(), m_texture->getTextureId());
		//
		//}
		/*for (auto Alpha : m_planesAlpha) {
			Alpha->render(m_shader, m_camera->getModelMatrix(), m_camera->getProjectionMatrix());
		}*/
}


	void update(float deltaTime, GLFWwindow* window) {
		/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		checkGLError();*/

		int i=1;
		for (auto object : m_gameobjects) 
		{
			float rotationDir = (i % 2 == 0) ? 0.1f : -0.1f;
			object.second->setRotationZ(object.second->getRotationZ() + (i * deltaTime * rotationDir));

			++i;
		}

		int inputx = 0;
		int inputy = 0;

		int state = glfwGetKey(window, GLFW_KEY_W);
		if (state == GLFW_PRESS) 
		{
			inputy += 10;
		}

		state = glfwGetKey(window, GLFW_KEY_S);
		if (state == GLFW_PRESS)
		{
			inputy += -10;
		}

	     state = glfwGetKey(window, GLFW_KEY_D);
		if (state == GLFW_PRESS)
		{
			inputx += 10;
		}

		 state = glfwGetKey(window, GLFW_KEY_A);
		if (state == GLFW_PRESS)
		{
			inputx += -10;
		}
		player->input(inputx, inputy);
	}

private:
	Texture* kamk;             // Texture id
	Texture* tiki;             // Texture id
	Texture* helado;             // Texture id

	std::vector<Texture*> m_textures;

	Camera* m_camera;              //Camera
	Shader* m_shader;              // Pointer to the Shader object
	SpriteBatch* m_spriteBatch;    // SpriteBatch.
	SpriteBatch* m_playerSpriteBatch;    // SpriteBatch.

	std::multimap<Texture*, GameObject*> m_gameobjects;

	//std::vector<GameObject*> m_gameObjects;  // Vector of gameobject pointers.
	//std::vector<Player*> m_players;


	//std::vector<Plane*> m_planes; // Pointer to the Plane object.
	//std::vector<Plane*> m_planesAlpha;    // Vector to transparent planes pointers.

};

// Global pointer to the application
Application* g_app = 0;

int main() {
	// Set c++-lambda as error call back function for glfw.
	glfwSetErrorCallback([](int error, const char* description) {
		fprintf(stderr, "Error %d: %s\n", error, description);
		});

	// Try to initialize glfw
	if (!glfwInit()) {
		return -1;
	}

	// Create window and check that creation was succesful.
	GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL window", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// Set current context
	glfwMakeContextCurrent(window);
	// Load GL functions using glad
	gladLoadGL(glfwGetProcAddress);

	// Create application
	g_app = new Application();

	// Specify the key callback as c++-lambda to glfw
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		// Close window if escape is pressed by the user.
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		});

	// Get time using glfwGetTime-function, for delta time calculation.
	float prevTime = (float)glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		// Render the game frame and swap OpenGL back buffer to be as front buffer.
		g_app->render(window);
		glfwSwapBuffers(window);

		// Poll other window events.
		glfwPollEvents();

		// Compute application frame time (delta time) and update application
		float curTime = (float)glfwGetTime();
		float deltaTime = curTime - prevTime;
		prevTime = curTime;
		g_app->update(deltaTime,window);
	}

	// Delete application
	delete g_app;
	g_app = 0;

	// Destroy window
	glfwDestroyWindow(window);

	// Terminate glfw
	glfwTerminate();

	return 0;
}
