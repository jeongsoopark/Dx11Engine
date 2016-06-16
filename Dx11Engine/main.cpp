

#include "FrameWork.h"

void main()
{
	FrameWork* framework = new FrameWork();

	if (framework->Init())
	{
		framework->Run();
	}

	delete framework;
	return;
}