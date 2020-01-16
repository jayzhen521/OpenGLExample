#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include <cmath>

#include "LoadShaders.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

GLint gWorldLocation = 0xFFFFFFFF;

struct Vector3f
{
    float vec[3];
};

struct Matrix4f
{
    float m[4][4];
};

Matrix4f World;

void display(void)
{
    static float Scale = 0.0f;
    Scale += 0.001f;

    World.m[0][0] = sinf(Scale);
    World.m[1][1] = sinf(Scale);
    World.m[2][2] = sinf(Scale);

    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &World.m[0][0]);

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(int argc, char** argv)
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Background", NULL, NULL);
    glfwMakeContextCurrent(window);
    gl3wInit();

    Vector3f Vertices[3];
    Vertices[0] = { -1.0f, -1.0f, 0.0f };
    Vertices[1] = { 1.0f, -1.0f, 0.0f };
    Vertices[2] = { 0.0f, 1.0f, 0.0f };

    ShaderInfo shaders[] = {
        {GL_VERTEX_SHADER, "shaders/triangles.vert"},
        {GL_FRAGMENT_SHADER, "shaders/triangles.frag"},
        {GL_NONE, NULL}
    };
    GLuint program = LoadShaders(shaders);
    glUseProgram(program);

    gWorldLocation = glGetUniformLocation(program, "gWorld");
    assert(gWorldLocation != 0xFFFFFFFF);
    
    World.m[0][0] = 1.0f; World.m[0][1] = 0.0f; World.m[0][2] = 0.0f; World.m[0][3] = 0.0f;
    World.m[1][0] = 0.0f; World.m[1][1] = 1.0f; World.m[1][2] = 0.0f; World.m[1][3] = 0.0f;
    World.m[2][0] = 0.0f; World.m[2][1] = 0.0f; World.m[2][2] = 1.0f; World.m[2][3] = 0.0f;
    World.m[3][0] = 0.0f; World.m[3][1] = 0.0f; World.m[3][2] = 0.0f; World.m[3][3] = 1.0f;

    GLuint VBO;
    glCreateBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

    while (!glfwWindowShouldClose(window))
    {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glfwDestroyWindow(window);

    glfwTerminate();
}
