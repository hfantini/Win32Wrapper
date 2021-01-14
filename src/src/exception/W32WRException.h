#pragma once

#include "../../pch.h";

namespace Win32Wrapper
{
	class W32WRException : public std::exception
	{
		public: 

			static enum class Type { WARNING = 1, ERR = 2, FATAL = 3 };

			W32WRException(const char* msg);
			~W32WRException();

		private: 

		protected: 

	};
}