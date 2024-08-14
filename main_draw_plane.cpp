#include <stdio.h>			// Include stdio.h, which contains printf-function
#include <kgfw/Object.h>	// Include kgfw::Object
#include <glad/gl.h>		// Include glad
#include <GLFW/glfw3.h>		// Include glfw
#include <kgfw/GLUtils.h>

class Application : public kgfw::Object
{
public:
	Application() : Object(__FUNCTION__) {
		const char *vertexShaderSource =
			// specify which version of GLSL should be used to compile/link a shader. This example uses version 3.3.
			"#version 330 core\n"
			// Specify that in location 0 are positions of the primitive.
			"layout (location = 0) in vec3 position;\n"
			// Vertex shader main function.
			"void main()\n"
			"{\n"
			// Write position to gl_Position output variable.
			"   gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
			"}";

		const char *fragmentShaderSource = 
			// specify which version of GLSL should be used to compile/link a shader. This example uses version 3.3.
			"#version 330 core\n"
			// Declare fragment shader output
			"out vec4 FragColor;\n"
			// Fragment shader main function.
			"void main()\n"
			"{\n"
			// Set output to be white pixel for each fragment of the primitive to draw
			"   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
			"}";

		// build and compile our shader program
		// ------------------------------------

		// Create and compile vertex shader
		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		checkGLError();
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		checkGLError();
		glCompileShader(vertexShader);
		checkGLError();

		// check for shader compile errors
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		checkGLError();
		if (!success) {
			// If failed, get error string using glGetShaderInfoLog-function.
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			checkGLError();
			printf("ERROR: Shader compilation failed: \"%s\"\n", infoLog);
		}

		// Create and compile fragment shader
		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		checkGLError();
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		checkGLError();
		glCompileShader(fragmentShader);
		checkGLError();
		// check for shader compile errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		checkGLError();
		if (!success) {
			// If failed, get error string using glGetShaderInfoLog-function.
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			checkGLError();
			printf("ERROR: Shader compilation failed: \"%s\"\n", infoLog);
		}

		// link shaders
		m_shaderProgram = glCreateProgram();
		checkGLError();
		glAttachShader(m_shaderProgram, vertexShader);
		checkGLError();
		glAttachShader(m_shaderProgram, fragmentShader);
		checkGLError();
		glLinkProgram(m_shaderProgram);
		checkGLError();
		// check for linking errors
		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
		checkGLError();
		if (!success) {
			// If failed, get error string using glGetProgramInfoLog-function.
			glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
			checkGLError();
			printf("ERROR: Shader link failed: \"%s\"\n", infoLog);
		}

		// After linking, the shaders can be deleted.
		glDeleteShader(vertexShader);
		checkGLError();
		glDeleteShader(fragmentShader);
		checkGLError();

		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------

		// Vertices to draw a triangle.
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, // left  
			 0.5f, -0.5f, 0.0f, // right 
			-0.5f,  0.5f, 0.0f,  // top   
			-0.5f,  0.5f, 0.0f, // left  
			 0.5f,  -0.5f, 0.0f, // right 
			 0.5f,  0.5f, 0.0f,  // top   

		};

		// Create Vertex Array Object
		glGenVertexArrays(1, &m_vao);
		checkGLError();
		
		// Create Vertex Buffer Object
		glGenBuffers(1, &m_vbo);
		checkGLError();

		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then 
		// configure vertex attributes(s).
		glBindVertexArray(m_vao);
		checkGLError();

		// Set buffer data to m_vbo-object (bind buffer first and then set the data)
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		checkGLError();
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		checkGLError();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		checkGLError();
		glEnableVertexAttribArray(0);
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

	~Application() {
		// Delete shader program
		glDeleteProgram(m_shaderProgram);
		checkGLError();
		// Delete Vertex Buffer Object
		glDeleteBuffers(1, &m_vbo);
		checkGLError();
		// Delete Vertex Array Object
		glDeleteVertexArrays(1, &m_vao);
		checkGLError();
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

		// draw our first triangle:

		// Bind the shader program
		glUseProgram(m_shaderProgram);
		checkGLError();
		// Seeing as we only have a single VAO there's no need to bind it every time,
		// but we'll do so to keep things a bit more organized.
		glBindVertexArray(m_vao);
		checkGLError();
		// Draw 3 vertices as triangles
		glDrawArrays(GL_TRIANGLES, 0, 6);
		checkGLError();
	}

	void update(float deltaTime) {
	}

private:
	GLuint m_vbo;			// Handle to Vertex Buffer Object
	GLuint m_vao;			// Handle to Vertex Array Object
	GLint m_shaderProgram;	// Handle to the shader program
};

// Global pointer to the application
Application* g_app = 0;

int main(void) {
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
