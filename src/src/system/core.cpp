#include "../../pch.h"
#include "core.h"
#include "system.h"
#include "../exception/W32WRException.h"

#define W32WR_MESSAGE_W32WRException 0x123;

namespace Win32Wrapper
{
	Core::Core(HINSTANCE hInstance, View* view)
	{
		if (hInstance == NULL)
		{
			// THROW ERROR;
		}

		this->_hInstance = hInstance;
		this->_view = view;
	}

	Core::~Core()
	{

	}

	void Core::run(int nCmdShow)
	{
		try
		{
			// CREATE MAIN VIEW

			this->_view->create();
			this->_view->show(nCmdShow);

			// STARTS THE MESSAGE QUEUE

			MSG msg;
			while (GetMessage(&msg, NULL, 0, 0) > 0)
			{
				TranslateMessage(&msg);

				if (msg.message == W32WR_EXCEPTION)
				{
					throw ExceptionHandler::getException(msg.lParam);
				}
				else
				{
					DispatchMessage(&msg);
				}

				if ( !IsWindow( this->_view->getHandle() ) )
				{
					PostQuitMessage(0);
				}
			}
		}
		catch (W32WRException const& e)
		{
			MessageBoxA(NULL, e.what(), "ERROR!", MB_ICONERROR | MB_OK);
			System::exit(1);
		}
	}
}