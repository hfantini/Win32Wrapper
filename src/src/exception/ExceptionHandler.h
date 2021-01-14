#pragma once
#include "../../pch.h";
#include "W32WRException.h"

namespace Win32Wrapper
{
	class ExceptionHandler
	{
		public:

			static UINT registerException(W32WRException e);
			static W32WRException getException(UINT index);

		private:

			static std::vector<W32WRException> _exceptionVec;

		protected:

	};
}