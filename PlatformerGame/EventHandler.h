#pragma once

class EventHandler
{
private:
	// Key handler
	virtual void KeyReleased() = 0;
	virtual void KeyPressed() = 0;

	// Mouse button handler
	virtual void MouseButtonPressed() = 0;
	virtual void MouseButtonReleased() = 0;

	// Mouse move handler
	virtual void MouseEntered() = 0;
	virtual void MouseLeft() = 0;
	virtual void MouseMoved() = 0;

public:
	virtual void KeyEventHandler() = 0;
	virtual void MouseButtonEventHandler() = 0;
	virtual void MouseMoveEventHandler() = 0;
};

