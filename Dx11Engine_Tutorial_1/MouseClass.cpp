#include "MouseClass.h"



MouseClass::MouseClass()
{
}


MouseClass::~MouseClass()
{
}

void MouseClass::OnLeftPressed(int x, int y)
{
	this->mIsLeftDown = true; 
	MouseEvent event(MouseEvent::EventType::LPressed, x, y);
	this->mEventBuffer.push(event);
}

void MouseClass::OnLeftReleased(int x, int y)
{
	this->mIsLeftDown = false; 
	MouseEvent event(MouseEvent::EventType::LReleased, x, y);
	this->mEventBuffer.push(event);
}

void MouseClass::OnRightPressed(int x, int y)
{
	this->mIsRightDown = true; 
	MouseEvent event(MouseEvent::EventType::RPressed, x, y);
	this->mEventBuffer.push(event);
}

void MouseClass::OnRightReleased(int x, int y)
{
	this->mIsRightDown = false; 
	MouseEvent event(MouseEvent::EventType::RReleased, x, y);
	this->mEventBuffer.push(event);
}

void MouseClass::OnMiddlePressed(int x, int y)
{	this->mIsMiddleDown = true; 
	MouseEvent event(MouseEvent::EventType::MPressed, x, y);
	this->mEventBuffer.push(event);

}

void MouseClass::OnMiddleReleased(int x, int y)
{	
	this->mIsMiddleDown = false; 
	MouseEvent event(MouseEvent::EventType::MReleased, x, y);
	this->mEventBuffer.push(event);
}

void MouseClass::OnWheelUp(int x, int y)
{
	MouseEvent event(MouseEvent::EventType::WheelUp, x, y);
	this->mEventBuffer.push(event);
}

void MouseClass::OnWheelDown(int x, int y)
{
	MouseEvent event(MouseEvent::EventType::WheelDown, x, y);
	this->mEventBuffer.push(event);
}

void MouseClass::OnMouseMove(int x, int y)
{
	MouseEvent event(MouseEvent::EventType::Move, x, y);
	this->mEventBuffer.push(event);
}

void MouseClass::OnMouseMoveRaw(int x, int y)
{
	MouseEvent event(MouseEvent::EventType::RawMove, x, y);
	this->mEventBuffer.push(event);
}

bool MouseClass::IsLeftDown()
{
	return this->mIsLeftDown;
}

bool MouseClass::IsRightDown()
{
	return this->mIsRightDown;
}

bool MouseClass::IsMiddleDown()
{
	return this->mIsMiddleDown;
}

int MouseClass::GetPosX() const
{
	return this->x;
}

int MouseClass::GetPosY() const
{
	return this->y;
}

MousePosition MouseClass::GetPos() const
{
	return { this->x, this->y };
}

bool MouseClass::IsEventBufferEmpty() const
{
	return mEventBuffer.empty();
}

MouseEvent MouseClass::GetEvent()
{
	if (mEventBuffer.empty())
	{
		return MouseEvent();
	}
	else
	{
		MouseEvent e = mEventBuffer.front();
		mEventBuffer.pop();
		return e;
	}
}
