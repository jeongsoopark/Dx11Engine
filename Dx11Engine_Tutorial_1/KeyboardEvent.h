#pragma once
class KeyboardEvent
{
public:
	enum EventType
	{
		Press,
		Release,
		Invalid
	};

	KeyboardEvent();
	KeyboardEvent(const EventType type, const unsigned int key);
	~KeyboardEvent();

	bool IsPressed() const;
	bool IsReleased() const;
	bool IsValid() const;

	unsigned int GetKeyCode() const;

private :
	EventType mType;
	unsigned char mKey;
};

