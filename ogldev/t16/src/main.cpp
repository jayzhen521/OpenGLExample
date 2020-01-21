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
#include "Vertex.h"
#include "Texture.h"




GLint gWVP = 0xFFFFFFFF;
GLint gSampler = 0xFFFFFFFF;

GLuint VBO;
GLuint IBO;

Pipeline p;
std::shared_ptr<Camera> pCamera = nullptr;

std::shared_ptr<Texture> pTexture = nullptr;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    p.SetPerspectiveProj(30.0f / 180.0f * 3.14159f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 100.0f);
    p.SetCamera(pCamera);

    //glm using column major ordering, so transpose set to GL_FALSE
    glUniformMatrix4fv(gWVP, 1, GL_FALSE, glm::value_ptr(*p.GetTrans()));

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
        pCamera->OnMouse((uint32_t)xpos, (uint32_t)ypos);
    }
}

void createVertexBuffer()
{
    Vertex Vertices[4] = {
        {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.0f, -1.0f, 1.0f}, {0.5f, 0.0f}},
        {{1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.0f, 1.0f, 0.0f}, {0.5f, 1.0f}}
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

void createIndexBuffer()
{
    Index Indices[] = { 0, 1, 3,
                        1, 2, 3,
                        2, 0, 3,
                        0, 2, 1 };

    glCreateBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
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

    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

    createVertexBuffer();
    createIndexBuffer();

    pCamera = std::make_shared<Camera>(
        WINDOW_WIDTH, WINDOW_HEIGHT,
        glm::vec3(-45.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    ShaderInfo shaders[] = {
        {GL_VERTEX_SHADER, "shaders/triangles.vert"},
        {GL_FRAGMENT_SHADER, "shaders/triangles.frag"},
        {GL_NONE, NULL}
    };
    GLuint program = LoadShaders(shaders);
    glUseProgram(program);

    glUniform1i(gSampler, 0);

    gWVP = glGetUniformLocation(program, "gWVP");
    assert(gWVP != 0xFFFFFFFF);
    gSampler = glGetUniformLocation(program, "gSampler");
    assert(gSampler != 0xFFFFFFFF);

    //
    pTexture = std::make_shared<Texture>(GL_TEXTURE_2D, "images/test.png");

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(Position)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    if (!pTexture->Load()) {
        return 1;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    pTexture->Bind(GL_TEXTURE0);

    while (!glfwWindowShouldClose(window))
    {
        pCamera->OnRender();
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glfwDestroyWindow(window);

    glfwTerminate();
}
