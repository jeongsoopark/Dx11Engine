

#include "FrameWork.h"

void main()
{
	FrameWork* framework = new FrameWork("DX Engine Ex1");

	if (framework->Init())
	{
		framework->Run();
	}

	delete framework;
	return;
}