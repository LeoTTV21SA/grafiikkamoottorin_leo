#include <stdio.h> // Include stdio.h, which contains printf-function
#include <kgfw/Object.h>  // Include kgfw::Object
#include <glad/gl.h>      // Include glad
#include <GLFW/glfw3.h>   // Include glfw


class Application : public kgfw::Object
{
public:
    Application() : Object(__FUNCTION__) {
    }

    void render(GLFWwindow* window) {
        // TODO: Application rendering/drawing code comes here
        // Query the size of the framebuffer (window content) from glfw.
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        // Setup the opengl viewport (i.e specify area to draw)
        glViewport(0, 0, width, height);

        // Set color to be used when clearing the screen
        glClearColor(1.0f, 0.5f, 0.0f, 1.0f);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

    }

    void update(float deltaTime) {
        // TODO: Game update function implementation comes here
    }
};
// Global pointer to the application
Application* g_app = 0;


// The main function of the application
int main() 
{
    //            INITIALIZATION
    // Set c++-lambda as error callback function for glfw.
    glfwSetErrorCallback([](int error, const char* description) {
        fprintf(stderr, "Error %d: %s\n", error, description);
        });

    // Try to initialize glfw
    if (!glfwInit()) {
        return -1;
    }

    // Create window and check that creation was successful.
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
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
    {
        // Close window if escape is pressed by the user.
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    });

    //       GAME LOOP
   // Get time using glfwGetTime-function, for delta time calculation.
   float prevTime = (float)glfwGetTime();
   while (!glfwWindowShouldClose(window)) 
   {
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

   //    CLEANUP

       // Delete application
      delete g_app;
      g_app = 0;

     // Destroy window
   glfwDestroyWindow(window);

    // Terminate glfw
    glfwTerminate();

    // Print "Hello world!"-text
    printf("Hello world!\n");
}
