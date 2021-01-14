#include "../../pch.h"
#include "control.h"
#include "../system/system.h"
#include "../exception/W32WRException.h"

namespace Win32Wrapper
{
	Control::Control(HINSTANCE hInstance, Component* guiElement, wstring className) : Component(hInstance, guiElement)
	{
		this->_className = new wstring(className);
	}

	Control::~Control()
	{

	}

	void Control::registerClass()
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

	void Control::show()
	{
		if (this->getHandle() == NULL)
		{
			throw "ERROR";
		}

		ShowWindow(this->getHandle(), SW_NORMAL);
		UpdateWindow(this->getHandle());
	}

	void Control::hide()
	{
		if (this->getHandle() == NULL)
		{
			throw "ERROR";
		}

		ShowWindow(this->getHandle(), SW_HIDE);
	}

	void Control::onCreate(HWND hWnd)
	{
		Component::onCreate(hWnd);

		this->setPosition(DoubleVector<long>(0, 0));
		this->setSize(DoubleVector<long>(300, 100));
	}

	void Control::onDestroy(HWND hWnd)
	{
		Component::onDestroy(hWnd);
	}

	void Control::onPositionChanged(UINT x, UINT y)
	{
		UpdateWindow(this->getHandle());
	}

	void Control::onSizeChanged(UINT type, UINT width, UINT height)
	{
		UpdateWindow(this->getHandle());
	}

	LRESULT CALLBACK Control::staticWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Control* pThis = NULL;

		try
		{
			if (msg == WM_NCCREATE)
			{
				LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
				pThis = static_cast<Control*>(lpcs->lpCreateParams);

				SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
			}
			else
			{
				pThis = reinterpret_cast<Control*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
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
			pThis->dispatchException(W32WRException(e.what()));
		}
	}

}