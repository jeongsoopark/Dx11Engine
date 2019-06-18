#include "KeyboardEvent.h"



KeyboardEvent::KeyboardEvent()
{
}


KeyboardEvent::~KeyboardEvent()
{
}

unsigned char KeyboardEvent::GetKeyCode() const
{
	return mKey;
}

KeyboardEvent::KeyboardEvent(const EventType type, const unsigned int key) :mType(type), mKey(key)
{

}


