#include "MouseEvent.h"



MouseEvent::MouseEvent()
{
}

MouseEvent::MouseEvent(MouseEvent::EventType type, int x, int y)
	:
	mType(type)
{
	mPosition.x = x;
	mPosition.y = y;
}


MouseEvent::~MouseEvent()
{
}

bool MouseEvent::IsValid() const
{
	return (this->mType != MouseEvent::EventType::Invalid);
}

MouseEvent::EventType MouseEvent::GetType() const
{
	return this->mType;
}

MousePosition MouseEvent::GetPos() const
{
	return this->mPosition;
}

int MouseEvent::GetPosX() const
{
	return this->mPosition.x;
}

int MouseEvent::GetPosY() const
{
	return this->mPosition.y;
}
