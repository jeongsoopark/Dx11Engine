#pragma once
struct MousePosition
{
	int x;
	int y;
};

class MouseEvent
{
public:
	enum EventType
	{
		LPressed,
		LReleased,
		RPressed,
		RReleased,
		MPressed,
		MReleased,
		WheelUp,
		WheelDown,
		Move,
		RawMove,
		Invalid
	};
	MouseEvent();
	MouseEvent(EventType type, int x, int y);
	~MouseEvent();

	bool IsValid() const;
	EventType GetType() const;
	MousePosition GetPos() const;
	int GetPosX() const;
	int GetPosY() const;

private:
	EventType mType;
	MousePosition mPosition;
};

