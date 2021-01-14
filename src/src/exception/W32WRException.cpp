#include "../../pch.h"
#include "W32WRException.h"

namespace Win32Wrapper
{
	W32WRException::W32WRException(const char* message) : std::exception(message)
	{

	}

	W32WRException::~W32WRException()
	{

	}
}