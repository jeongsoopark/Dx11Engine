#pragma once
#include "MouseEvent.h"
#include <queue>


class MouseClass
{
public:
	MouseClass();
	~MouseClass();
	void OnLeftPressed(int x, int y);
	void OnLeftReleased(int x, int y);
	void OnRightPressed(int x, int y);
	void OnRightReleased(int x, int y);
	void OnMiddlePressed(int x, int y);
	void OnMiddleReleased(int x, int y);

	void OnWheelUp(int x, int y);
	void OnWheelDown(int x, int y);
	void OnMouseMove(int x, int y);
	void OnMouseMoveRaw(int x, int y);

	bool IsLeftDown();
	bool IsRightDown();
	bool IsMiddleDown();
	
	int GetPosX() const;
	int GetPosY() const;
	MousePosition GetPos() const;

	bool IsEventBufferEmpty() const;
	MouseEvent GetEvent();

private:
	std::queue<MouseEvent> mEventBuffer;
	bool mIsLeftDown = false;
	bool mIsRightDown = false;
	bool mIsMiddleDown = false;
	int x = 0;
	int y = 0;

};

