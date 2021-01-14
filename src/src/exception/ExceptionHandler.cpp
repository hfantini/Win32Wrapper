#pragma once
#include "../../pch.h"
#include "ExceptionHandler.h"

namespace Win32Wrapper
{
	std::vector<W32WRException> ExceptionHandler::_exceptionVec;

	UINT ExceptionHandler::registerException(W32WRException e)
	{
		ExceptionHandler::_exceptionVec.push_back(e);
		return ExceptionHandler::_exceptionVec.size() - 1;
	}

	W32WRException ExceptionHandler::getException(UINT index)
	{
		if (ExceptionHandler::_exceptionVec.empty())
		{
			return W32WRException("Exception not registered.");
		}

		if (index < 0 && index > ExceptionHandler::_exceptionVec.size() - 1)
		{
			return W32WRException("Invalid Range.");
		}

		return ExceptionHandler::_exceptionVec[index];
	}
}