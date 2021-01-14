#include "../../pch.h"
#include "view.h"
#include "../system/system.h"
#include "../exception/W32WRException.h"

namespace Win32Wrapper
{
	View::View(HINSTANCE hInstance, Component* guiElement, wstring className) : Component(hInstance, guiElement )
	{
		this->_className = new wstring(className);
	}


	View::~View()
	{

	}

	void View::registerClass()
	{
		Component::registerClass();

		if (!GetClassInfoExW(this->getInstance(), this->_className->c_str(), NULL))
		{
			WNDCLASSEXW wc;
			wc.cbSize = sizeof(WNDCLASSEXW);
			wc.style = 0;
			wc.lpfnWndProc = this->staticWindowProc;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = this->getInstance();
			wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wc.lpszMenuName = NULL;
			wc.lpszClassName = this->_className->c_str();
			wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

			if (!RegisterClassExW(&wc))
			{
				throw "ERROR";
			}
		}
	}

	void View::create()
	{
		Component::create();

		HWND hWndParent = NULL;

		if (this->getParent() != NULL)
		{
			hWndParent = this->getParent()->getHandle();
		}

		if (this->getHandle() == NULL)
		{
			this->_hWnd = CreateWindowExW(
				WS_EX_CLIENTEDGE,
				this->_className->c_str(),
				L"WINDOW",
				WS_OVERLAPPEDWINDOW,
				100,
				100,
				500,
				300,
				hWndParent,
				NULL,
				this->getInstance(),
				this
			);
		}
	}

	void View::show(int nCmdShow)
	{
		if (this->getHandle() == NULL)
		{
			throw "ERROR";
		}

		if (nCmdShow < 0 || nCmdShow > 11)
		{
			throw "ERROR";
		}

		ShowWindow( this->getHandle(), nCmdShow );
		UpdateWindow( this->getHandle() );
	}

	void View::show()
	{
		this->show(SW_NORMAL);
	}

	void View::hide()
	{
		if (this->getHandle() == NULL)
		{
			throw "ERROR";
		}

		ShowWindow(this->getHandle(), SW_HIDE);
	}

	void View::onCreate(HWND hWnd)
	{
		Component::onCreate(hWnd);

		this->setTitle((wchar_t*)L"WINDOW");
		this->setPosition(DoubleVector<long>(50, 50));
		this->setSize(DoubleVector<long>(300, 300));
	}

	void View::onDestroy(HWND hWnd)
	{
		Component::onDestroy(hWnd);
	}

	LRESULT CALLBACK View::staticWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Component* pThis = NULL;

		try
		{
			if (msg == WM_NCCREATE)
			{
				LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
				pThis = static_cast<View*>(lpcs->lpCreateParams);

				SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
			}
			else
			{
				pThis = reinterpret_cast<View*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			}

			if (pThis != NULL)
			{
				return pThis->windowProc(hWnd, msg, wParam, lParam);
			}
			else
			{
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}
		}
		catch (std::exception const& e)
		{
			pThis->dispatchException( W32WRException(e.what()) );
		}
	}
}