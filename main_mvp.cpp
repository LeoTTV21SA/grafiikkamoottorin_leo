#include <stdio.h>			// Include stdio.h, which contains printf-function
#include <kgfw/Object.h>	// Include kgfw::Object
#include <glad/gl.h>		// Include glad
#include <GLFW/glfw3.h>		// Include glfw
#include <kgfw/GLUtils.h>
//#include "shader.h"
#include "plane.h"
#include <vector>
#include <iostream>
#include "camera.h"
#include "gameobject.h"



class Application : public GameObject
{
public:
	Application() : GameObject(__FUNCTION__){
		
		const char* vertexShaderSource =
			// specify which version of GLSL should be used to compile/link a shader. This example uses version 3.3.
			"#version 330 core\n"
			// Specify that in location 0 are positions of the primitive.
			"layout (location = 0) in vec3 position;\n"
			"uniform mat4 MVP;\n"
			// Vertex shader main function.
			"void main()\n"
			"{\n"
			// Write position to gl_Position output variable.
			"    gl_Position = MVP * vec4(position.x, position.y, position.z, 1.0);\n"
			"}";

		const char* fragmentShaderSource =
			// specify which version of GLSL should be used to compile/link a shader. This example uses version 3.3.
			"#version 330 core\n"
			"uniform vec3 color;\n"
			// Declare fragment shader output
			"out vec4 FragColor;\n"
			// Fragment shader main function.
			"void main()\n"
			"{\n"
			// Set output to be white pixel for each fragment of the primitive to draw
			
		  " FragColor = vec4(color.x,color.y, color.z, 1.0f);\n"
			"}";



		// Create ortho-projective camera with screen size 640x480
		m_camera = new Camera(0, 640, 0, 480);

		// Set camera transform (view transform)
		m_camera->setPosition(glm::vec3(-10.0f, -10.0f, 0.0f));

		// Build and compile our shader program
		m_shader = new Shader(vertexShaderSource, fragmentShaderSource);

		// Create planes
		m_planes.push_back(new Plane(0.0f, 0.0f, 1.0f, 1.0f));
		m_planes.push_back(new Plane(0.0f, 0.0f, 1.0f, 1.0f));
		m_planes.push_back(new Plane(0.0f, 0.0f, 1.0f, 1.0f));
		m_planes.push_back(new Plane(0.0f, 0.0f, 1.0f, 1.0f));

		m_planes[0]->setColor(1.0f, 0.0f, 0.0f);
		m_planes[1]->setColor(0.0f, 1.0f, 0.0f);
		m_planes[2]->setColor(0.0f, 0.0f, 1.0f);
		m_planes[3]->setColor(1.0f, 0.0f, 1.0f);

		m_planes[0]->setPosition(glm::vec3(50.0f, 50.0f, 0.0f));
		m_planes[1]->setPosition(glm::vec3(130.0f, 130.0f, 0.0f));
		m_planes[2]->setPosition(glm::vec3(230.0f, 230.0f, 0.0f));
		m_planes[3]->setPosition(glm::vec3(350.0f, 350.0f, 0.0f));

		m_planes[0]->setScaling(glm::vec3(70.0f, 70.0f, 1.0f));
		m_planes[1]->setScaling(glm::vec3(90.0f, 90.0f, 1.0f));
		m_planes[2]->setScaling(glm::vec3(110.0f, 110.0f, 1.0f));
		m_planes[3]->setScaling(glm::vec3(130.0f, 130.0f, 1.0f));
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

		// draw planes
		for (auto plane : m_planes) {
			plane->render(m_shader, m_camera->getModelMatrix(), m_camera->getProjectionMatrix());
		}

	}


	void update(float deltaTime) {
		float i = 1.0f;
		for (auto plane : m_planes) {
			plane->setRotationZ(plane->getRotationZ() + i++ * 3.14f * deltaTime);
		}
	}

	

private:
	Camera* m_camera; //Camera
	Shader* m_shader;             // Pointer to the Shader object
	std::vector<Plane*> m_planes; // Pointer to the Plane object.


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
