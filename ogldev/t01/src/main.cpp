#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Background", NULL, NULL);
    glfwMakeContextCurrent(window);
    gl3wInit();

    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

    while (!glfwWindowShouldClose(window))
    {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}
