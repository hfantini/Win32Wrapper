#include "../../pch.h"
#include "system.h"

namespace Win32Wrapper
{
	void System::exit(int statusCode)
	{
		PostQuitMessage(statusCode);
	}

	void System::exit()
	{
		System::exit(0);
	}
}