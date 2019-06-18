#pragma once
#include "KeyboardEvent.h"
#include <queue>

class KeyboardClass
{
public:
	KeyboardClass();
	~KeyboardClass();

	bool IsKeyPressed(const unsigned char keycode);
	bool IsKeyBufferEmpty();
	bool IsCharBufferEmpty();
	KeyboardEvent ReadKey();
	unsigned char ReadChar();

	void OnKeyPressed(const unsigned char key);
	void OnKeyReleased(const unsigned char key);
	void OnChar(const unsigned char key);
	void EnableAutoRepeatKeys();
	void DisableAutoRepeatKeys();
	void EnableAutoRepeatChars();
	void DisableAutoRepeatChars();
	bool IsAutoRepeateKeys();
	bool IsAutoRepeateChars();

private:

	bool mAutoRepeatKeys = false;
	bool mAutoRepeatChars = false;
	bool mKeyStates[256];
	std::queue<KeyboardEvent> keyBuffer;
	std::queue<unsigned int> charBuffer;
};


