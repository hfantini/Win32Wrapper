#pragma once

#include "../../pch.h"
#include "messages.h"
#include "../view/view.h"

namespace Win32Wrapper
{
	class Core
	{
		public:

			Core(HINSTANCE hInstance, View* view);
			~Core();
			void run(int nCmdShow);

		private:

		protected:

			HINSTANCE _hInstance;
			View* _view;
	};
}