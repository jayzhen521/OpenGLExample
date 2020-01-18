#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include <cmath>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <iostream>

#include "LoadShaders.h"
#include "Pipeline.h"
#include "Camera.h"

GLint gWorldLocation = 0xFFFFFFFF;

Pipeline p;
std::shared_ptr<Camera> pCamera = nullptr;

void display(void)
{
    p.SetPerspectiveProj(30.0f / 180.0f * 3.14159f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 100.0f);
    p.SetCamera(pCamera);

    //glm using column major ordering, so transpose set to GL_FALSE
    glUniformMatrix4fv(gWorldLocation, 1, GL_FALSE, glm::value_ptr(*p.GetTrans()));

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
}

void SpecialKeyboardCB(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (pCamera != nullptr)
    {
        pCamera->OnKeyboard(key);
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (pCamera != nullptr)
    {
        std::cout << xpos << ", " << ypos << std::endl;
        pCamera->OnMouse((uint32_t)xpos, (uint32_t)ypos);
    }
}

int main(int argc, char** argv)
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Background", NULL, NULL);
    glfwMakeContextCurrent(window);
    gl3wInit();

    glfwSetKeyCallback(window, SpecialKeyboardCB);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    glfwSetCursorPos(window, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    pCamera = std::make_shared<Camera>(
        WINDOW_WIDTH, WINDOW_HEIGHT,
        glm::vec3(-45.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    glm::vec3 Vertices[4];
    Vertices[0] = { -1.0f, -1.0f, 0.0f };
    Vertices[1] = { 0.0f, -1.0f, 1.0f };
    Vertices[2] = { 1.0f, -1.0f, 0.0f };
    Vertices[3] = { 0.0f, 1.0f, 0.0f };

    unsigned int Indices[] = { 0, 1, 3,
                               1, 2, 3,
                               2, 0, 3,
                               0, 2, 1 };

    ShaderInfo shaders[] = {
        {GL_VERTEX_SHADER, "shaders/triangles.vert"},
        {GL_FRAGMENT_SHADER, "shaders/triangles.frag"},
        {GL_NONE, NULL}
    };
    GLuint program = LoadShaders(shaders);
    glUseProgram(program);

    gWorldLocation = glGetUniformLocation(program, "gWorld");
    assert(gWorldLocation != 0xFFFFFFFF);

    GLuint VBO;
    GLuint IBO;
    glCreateBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glCreateBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

    while (!glfwWindowShouldClose(window))
    {
        pCamera->OnRender();
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glfwDestroyWindow(window);

    glfwTerminate();
}
