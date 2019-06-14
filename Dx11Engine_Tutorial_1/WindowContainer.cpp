#include "WindowContainer.h"



WindowContainer::WindowContainer()
{
}


WindowContainer::~WindowContainer()
{
}

LRESULT WindowContainer::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CHAR:
	{
		unsigned char ch = static_cast<unsigned char>(wParam);
		if (mKeyboard.IsAutoRepeateChars())
		{
			mKeyboard.OnChar(ch);
		}
		else
		{
			const bool wasPressed = lParam & 0x40000000;
			if (!wasPressed)
			{
				mKeyboard.OnChar(ch);
			}
		}
		return 0;
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
