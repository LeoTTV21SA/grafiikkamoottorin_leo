#include <stdio.h>			// Include stdio.h, which contains printf-function
#include <kgfw/Object.h>	// Include kgfw::Object
#include <glad/gl.h>		// Include glad
#include <GLFW/glfw3.h>		// Include glfw
#include <kgfw/GLUtils.h>
#include "plane.h"
#include <vector>
#include <iostream>
#include "camera.h"
#include "gameobject.h"
#include <algorithm>



class Application : public GameObject
{
public:
	Application() : GameObject(__FUNCTION__){
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

		
		const char* vertexShaderSource =
			// specify which version of GLSL should be used to compile/link a shader. This example uses version 3.3.
			"#version 330 core\n"
			// Specify that in location 0 are positions of the primitive.
			"layout (location = 0) in vec3 position;\n"

			// Texture coordinate of the vertex at location 1
			"layout (location = 1) in vec2 texCoordi;\n"
			"uniform mat4 MVP;\n"

			// Vertex shader main function.
			  // Outgoing texture coordinate
			"out vec2 texCoord;"
			"void main()\n"
			"{\n"

			// Write position to gl_Position output variable.
			 // Pass texture coordinate to the fragment shader
			"   texCoord = texCoordi;\n"
			"   gl_Position = MVP * vec4(position.x, position.y, position.z, 1.0);\n"
			"}";


		const char* fragmentShaderSource =
			// specify which version of GLSL should be used to compile/link a shader. This example uses version 3.3.
			"#version 330 core\n"
			"uniform vec4 color;\n"

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


		// Create texture
		glGenTextures(1, &m_textureId);
		checkGLError();
		// Bind it for use
		glBindTexture(GL_TEXTURE_2D, m_textureId);
		checkGLError();
		// This needs to be called because on some cases the texture data has some different row alignment. For more info see: https://www.khronos.org/opengl/wiki/Pixel_Transfer#Pixel_layout
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		// set the texture data as RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		checkGLError();
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


		// Create ortho-projective camera with screen size 640x480
		m_camera = new Camera(0, 640, 0, 480);

		// Set camera transform (view transform)
		m_camera->setPosition(glm::vec3(-10.0f, -10.0f, 0.0f));

		// Build and compile our shader program
		m_shader = new Shader(vertexShaderSource, fragmentShaderSource);

		// Create planes
		m_planes.push_back(new Plane(0.0f, 0.0f, 1.0f, 1.0f));
		/*m_planes.push_back(new Plane(0.0f, 0.0f, 1.0f, 1.0f));
		m_planes.push_back(new Plane(0.0f, 0.0f, 1.0f, 1.0f));
		m_planes.push_back(new Plane(0.0f, 0.0f, 1.0f, 1.0f));*/

		m_planes[0]->setColor(1.0f, 0.0f, 0.0f);
		/*m_planes[1]->setColor(0.0f, 1.0f, 0.0f);
		m_planes[2]->setColor(0.0f, 0.0f, 1.0f);
		m_planes[3]->setColor(1.0f, 0.0f, 1.0f);*/

		m_planes[0]->setPosition(glm::vec3(320.0f, 240.0f, 1.0f));
		/*m_planes[1]->setPosition(glm::vec3(340.0f, 250.0f, 0.8f));
		m_planes[2]->setPosition(glm::vec3(380.0f, 260.0f, 0.6f));
		m_planes[3]->setPosition(glm::vec3(420.0f, 270.0f, 0.4f));*/

		m_planes[0]->setScaling(glm::vec3(240.0f, 240.0f, 1.0f));
		/*m_planes[1]->setScaling(glm::vec3(160.0f, 120.0f, 1.0f));
		m_planes[2]->setScaling(glm::vec3(160.0f, 120.0f, 1.0f));
		m_planes[3]->setScaling(glm::vec3(160.0f, 120.0f, 1.0f));*/

		// Create planes with alpha
		//m_planesAlpha.push_back(new Plane(0.0f, 0.0f, 160.0f, 200.0f));
		//m_planesAlpha.push_back(new Plane(0.0f, 0.0f, 160.0f, 200.0f));

		//m_planesAlpha[0]->setColor(1.0f, 1.0f, 1.0f, 0.5f); // transparent white
		//m_planesAlpha[1]->setColor(0.1f, 0.1f, 0.9f, 0.25f); // transparent blue, like color

		//m_planesAlpha[0]->setPosition(glm::vec3(380.0f, 260.0f, 0.0f));
		//m_planesAlpha[1]->setPosition(glm::vec3(420.0f, 270.0f, 0.1f));

		//m_planesAlpha[0]->setRotationZ(glm::quarter_pi<float>());
		//m_planesAlpha[1]->setRotationZ(glm::quarter_pi<float>());

	}

		
		

	~Application() {
		// Delete shader
		delete m_shader;
		m_shader = 0;

		delete m_camera;
		m_camera = 0;

		for (auto plane : m_planes) {
			delete plane;
		}
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
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		checkGLError();

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);
		checkGLError();


		//Sort The planesAlpha by depth (ascending order, wher the smallest z is first to render)

		/*std::sort(m_planesAlpha.begin(), m_planesAlpha.end(), [](Plane* lhs, Plane* rhs)->bool {
			return lhs->getPosition().z < rhs->getPosition().z;
			});*/

		//Sort The planes by depth (ascending order, wher the smallest z is first to render)

		std::sort(m_planes.begin(), m_planes.end(), [](Plane* lhs, Plane* rhs)->bool {
			return lhs->getPosition().z < rhs->getPosition().z;
			});

		
		// draw planes
		for (auto plane : m_planes) {
			plane->render(m_shader, m_camera->getModelMatrix(), m_camera->getProjectionMatrix(),m_textureId);
		
		}
		/*for (auto Alpha : m_planesAlpha) {
			Alpha->render(m_shader, m_camera->getModelMatrix(), m_camera->getProjectionMatrix());
		}*/
	}


	void update(float deltaTime) {
		/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		checkGLError();*/

		//float i = 1.0f;
		//for (auto plane : m_planes) {
			//plane->setRotationZ(plane->getRotationZ() +  3.14f * deltaTime); //plane->setRotationZ(plane->getRotationZ() + i++ * 3.14f * deltaTime); el original
		//}
	}

	

private:
	GLuint m_textureId;          //Texture id.
	Camera* m_camera;              //Camera
	Shader* m_shader;             // Pointer to the Shader object
	std::vector<Plane*> m_planes; // Pointer to the Plane object.
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
		g_app->update(deltaTime);
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
