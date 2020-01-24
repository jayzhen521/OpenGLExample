#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>

#include "GlfwSupport.h"
#include "ICallbacks.h"

void GlfwSupport::SetEnvironment(std::shared_ptr<ICallbacks> pCallbacks)
{
	m_pCallbacks = pCallbacks;

	InitCallbacks();
}

KEY GlfwSupport::GlfwKeyToKey(uint Key)
{
	switch (Key) {
	case GLFW_KEY_F1:
		return KEY::KEY_F1;
	case GLFW_KEY_F2:
		return KEY::KEY_F2;
	case GLFW_KEY_F3:
		return KEY::KEY_F3;
	case GLFW_KEY_F4:
		return KEY::KEY_F4;
	case GLFW_KEY_F5:
		return KEY::KEY_F5;
	case GLFW_KEY_F6:
		return KEY::KEY_F6;
	case GLFW_KEY_F7:
		return KEY::KEY_F7;
	case GLFW_KEY_F8:
		return KEY::KEY_F8;
	case GLFW_KEY_F9:
		return KEY::KEY_F9;
	case GLFW_KEY_F10:
		return KEY::KEY_F10;
	case GLFW_KEY_F11:
		return KEY::KEY_F11;
	case GLFW_KEY_F12:
		return KEY::KEY_F12;
	case GLFW_KEY_LEFT:
		return KEY::KEY_LEFT;
	case GLFW_KEY_UP:
		return KEY::KEY_UP;
	case GLFW_KEY_RIGHT:
		return KEY::KEY_RIGHT;
	case GLFW_KEY_DOWN:
		return KEY::KEY_DOWN;
	case GLFW_KEY_PAGE_UP:
		return KEY::KEY_PAGE_UP;
	case GLFW_KEY_PAGE_DOWN:
		return KEY::KEY_PAGE_DOWN;
	case GLFW_KEY_HOME:
		return KEY::KEY_HOME;
	case GLFW_KEY_END:
		return KEY::KEY_END;
	case GLFW_KEY_INSERT:
		return KEY::KEY_INSERT;
	case GLFW_KEY_DELETE:
		return KEY::KEY_DELETE;
	default:
		std::cerr << "Unimplemented GLFW key" << std::endl;
	}

	return KEY::KEY_UNDEFINED;
}

void GlfwSupport::GlfwBackendInit(int argc, char** argv, bool withDepth = true, bool withStencil = true)
{
	m_WithDepth = withDepth;
	m_WithStencil = withStencil;

	glfwInit();
}

bool GlfwSupport::GlfwCreateWindow(u32 width, u32 height, const std::string& title)
{
	m_pWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	glfwMakeContextCurrent(m_pWindow);
	return true;
}

void GlfwSupport::GlfwDestroyWindow()
{
	glfwDestroyWindow(m_pWindow);
}

void GlfwSupport::GlfwTerminate()
{
	glfwTerminate();
}

MOUSE_BUTTON GlfwSupport::GlfwMouseButtonToMouseButton(int button)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		return MOUSE_BUTTON::MOUSE_BUTTON_LEFT;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		return MOUSE_BUTTON::MOUSE_BUTTON_MIDDLE;
	case GLFW_MOUSE_BUTTON_RIGHT:
		return MOUSE_BUTTON::MOUSE_BUTTON_RIGHT;
	default:
		std::cerr << "Unimplemented GLFW mouse button" << std::endl;
	}
	return MOUSE_BUTTON::MOUSE_UNDEFINED;
}

BUTTON_ACTION GlfwSupport::GlfwButtonActionToButtonAction(int glfwAction)
{
	switch (glfwAction)
	{
	case GLFW_PRESS:
		return BUTTON_ACTION::BUTTON_ACTION_PRESS;
	case GLFW_RELEASE:
		return BUTTON_ACTION::BUTTON_ACTION_RELEASE;
	default:
		std::cerr << "Unimplemented GLFW button action" << std::endl;
	}
	return BUTTON_ACTION::BUTTON_ACTION_UNDEFINED;
}

void GlfwSupport::KeyboardCB(GLFWwindow* window, int glfwKey, int scancode, int action, int mods)
{
	KEY key = KEY::KEY_UNDEFINED;

	if (action == GLFW_PRESS)
	{
		if ((glfwKey >= '0') && (glfwKey <= '9') && mods == 0)
		{
			key = (KEY)glfwKey;
		}
		else if ((glfwKey >= 'A') && (glfwKey <= 'Z') && mods == GLFW_MOD_SHIFT || mods == GLFW_MOD_CAPS_LOCK)
		{
			key = (KEY)glfwKey;
		}
		else if ((glfwKey >= 'A') && (glfwKey <= 'Z') && (mods == 0 || (mods == (GLFW_MOD_CAPS_LOCK | GLFW_MOD_SHIFT))))
		{
			key = (KEY)(glfwKey + 32);
		}
		else
		{
			key = GlfwKeyToKey(glfwKey);
		}

		if (key == KEY::KEY_UNDEFINED)
			std::cerr << glfwKey << "Unimplemented GLFW key" << std::endl;

		m_pCallbacks->KeyboardCB(key);
	}

}

void GlfwSupport::PassiveMouseCB(GLFWwindow* window, double xpos, double ypos)
{
	m_pCallbacks->PassiveMouseCB((int)xpos, (int)ypos);
}

void GlfwSupport::MouseCB(GLFWwindow* window, int glfwButton, int glfwAction, int mods)
{
	MOUSE_BUTTON button = GlfwMouseButtonToMouseButton(glfwButton);
	BUTTON_ACTION action = GlfwButtonActionToButtonAction(glfwAction);
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	m_pCallbacks->MouseCB(button, action, (int)xpos, (int)ypos);
}

void GlfwSupport::Display()
{
	while (!glfwWindowShouldClose(m_pWindow))
	{
		m_pCallbacks->Display();
		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}
}

void GlfwSupport::InitCallbacks()
{
	glfwSetKeyCallback(m_pWindow, KeyboardCB);
	glfwSetCursorPosCallback(m_pWindow, PassiveMouseCB);
	//glfwSetMouseButtonCallback(m_pWindow, MouseCB);
	glfwSetCursorPos(m_pWindow, 400.0f, 400.0f);
}

bool GlfwSupport::isWithDepth()
{
	return m_WithDepth;
}

bool GlfwSupport::isWithStencil()
{
	return m_WithStencil;
}

GLFWwindow* GlfwSupport::m_pWindow = NULL;

bool GlfwSupport::m_WithDepth = false;

bool GlfwSupport::m_WithStencil = false;

std::shared_ptr<ICallbacks> GlfwSupport::m_pCallbacks = nullptr;
