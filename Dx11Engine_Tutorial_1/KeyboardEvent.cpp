#include "KeyboardEvent.h"



KeyboardEvent::KeyboardEvent()
{
}


KeyboardEvent::~KeyboardEvent()
{
}

KeyboardEvent::KeyboardEvent(const EventType type, const unsigned int key) :mType(type), mKey(key)
{
}
