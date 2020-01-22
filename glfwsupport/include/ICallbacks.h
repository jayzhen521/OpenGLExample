#pragma once

#include "Keys.h"

class ICallbacks
{
public:
	virtual void KeyboardCB(KEY key, BUTTON_ACTION keyState = BUTTON_ACTION::BUTTON_ACTION_PRESS) {}

	virtual void PassiveMouseCB(int x, int y) {}

	virtual void Display() {}

	virtual void MouseCB(MOUSE_BUTTON button, BUTTON_ACTION state, int x, int y) {}

	virtual void FrameSetting(bool withDepth, bool withStencil) {}
};