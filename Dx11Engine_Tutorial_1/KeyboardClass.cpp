#include "KeyboardClass.h"
#include <Windows.h>



KeyboardClass::KeyboardClass()
{
	for (int i = 0; i < 256; i++)
		this->mKeyStates[i] = false;
}


KeyboardClass::~KeyboardClass()
{
}

bool KeyboardClass::IsKeyPressed(const unsigned char keycode)
{
	return this->mKeyStates[keycode];

}

bool KeyboardClass::IsCharBufferEmpty()
{
	return this->charBuffer.empty();
}

bool KeyboardClass::IsKeyBufferEmpty()
{
	return this->keyBuffer.empty();
}

KeyboardEvent KeyboardClass::ReadKey()
{
	if (this->keyBuffer.empty())
	{
		return KeyboardEvent();
	}
	else
	{
		KeyboardEvent e = this->keyBuffer.front();
		this->keyBuffer.pop();
		return e;
	}
}

unsigned char KeyboardClass::ReadChar()
{
	if (this->charBuffer.empty())
	{
		return 0u;
	}
	else
	{
		unsigned char e = this->charBuffer.front();
		this->charBuffer.pop();
		return e;
	}
}


void KeyboardClass::OnKeyPressed(const unsigned char key)
{
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::Press, key));
}

void KeyboardClass::OnKeyReleased(const unsigned char key)
{
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::Release, key));
}

void KeyboardClass::OnChar(const unsigned char key)
{
	this->charBuffer.push(key);
}

void KeyboardClass::EnableAutoRepeatKeys()
{
	this->mAutoRepeatKeys = true;
}

void KeyboardClass::DisableAutoRepeatKeys()
{
	this->mAutoRepeatKeys = false;
}

void KeyboardClass::EnableAutoRepeatChars()
{
	this->mAutoRepeatChars = true;
}

void KeyboardClass::DisableAutoRepeatChars()
{
	this->mAutoRepeatChars = false;
}


bool KeyboardClass::IsAutoRepeateKeys()
{
	return this->mAutoRepeatKeys;
}

bool KeyboardClass::IsAutoRepeateChars()
{
	return this->mAutoRepeatChars;
}
