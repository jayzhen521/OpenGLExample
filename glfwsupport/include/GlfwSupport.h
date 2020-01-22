#pragma once

#include <memory>
#include <string>

#include "Keys.h"
#include "Types.h"

class ICallbacks;
struct GLFWwindow;

class GlfwSupport
{
public:
	static void SetEnvironment(std::shared_ptr<ICallbacks> pCallbacks);

	static KEY GlfwKeyToKey(uint Key);

	static void GlfwBackendInit(int argc, char** argv, bool withDepth, bool withStencil);

	static bool GlfwCreateWindow(u32 width, u32 height, const std::string& title);

	static void GlfwDestroyWindow();

	static void GlfwTerminate();

	static MOUSE_BUTTON GlfwMouseButtonToMouseButton(int glfwButton);

	static BUTTON_ACTION GlfwButtonActionToButtonAction(int glfwAction);

	//
	static void KeyboardCB(GLFWwindow* window, int key, int scancode, int action, int mods);

	//Passive motion means that the mouse moves without any of its buttons pressed
	static void PassiveMouseCB(GLFWwindow* window, double xpos, double ypos);

	//
	static void MouseCB(GLFWwindow* window, int button, int action, int mods);

	static void Display();

	static void InitCallbacks();

	static bool isWithDepth();

	static bool isWithStencil();

private:
	static GLFWwindow* m_pWindow;
	static bool m_WithDepth;
	static bool m_WithStencil;
	static std::shared_ptr<ICallbacks> m_pCallbacks;
};
