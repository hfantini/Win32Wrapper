#include "../../pch.h"
#include "component.h"
#include "messages.h"

namespace Win32Wrapper
{
	Component::Component(HINSTANCE hInstance, Component* parent)
	{
		if (hInstance == NULL)
		{
			// THROW ERROR
			return;
		}

		this->_parent = parent;
		this->_hInstance = hInstance;
	}

	Component::~Component()
	{
		this->unregisterClass();

		if (this->_className)
		{
			delete this->_className;
		}
	}

	void Component::registerClass()
	{

	}

	void Component::unregisterClass()
	{
		UnregisterClass(this->getClassName().c_str(), this->_hInstance);
	}

	void Component::create()
	{
		this->registerClass();
	}

	void Component::destroy()
	{
		if ( this->getHandle() != NULL )
		{
			if ( !DestroyWindow(this->getHandle() ) )
			{
				int error = GetLastError();
				throw error;
			}
		}
		else
		{
			throw W32WRException("Component not initialized/created.");
		}
	}

	void Component::onCreate(HWND hWnd)
	{

	}

	void Component::onDestroy(HWND hWnd)
	{
		
	}


	void Component::onPaint()
	{

	}

	void Component::onPositionChanged(UINT posX, UINT posY)
	{
		
	}

	void Component::onSizeChanged(UINT type, UINT width, UINT height)
	{
		
	}

	void Component::onTimerTick(UINT_PTR identifier)
	{

	}

	void Component::dispatchException(W32WRException e)
	{
		UINT index = ExceptionHandler::registerException(e);
		PostMessage(this->getHandle(), W32WR_EXCEPTION, index, NULL);
	}

	LRESULT CALLBACK Component::windowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (hWnd == NULL)
		{
			// THROW ERROR;
			return NULL;
		}
		else
		{
			this->_hWnd = hWnd;
		}

		switch (msg)
		{
			case WM_CREATE:
			{
				this->onCreate(hWnd);
			}
			break;

			case WM_DESTROY:
			{
				this->onDestroy(hWnd);
			}
			break;

			case WM_PAINT:
			{
				this->onPaint();
			}
			break;

			case WM_TIMER:
			{
				this->onTimerTick(wParam);
			}
			break;

			case WM_SIZE:
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				this->onSizeChanged(wParam, width, height);
				break;
			}
			break;

			case WM_MOVE:
			{
				UINT x = LOWORD(lParam);
				UINT y = HIWORD(lParam);
				this->onPositionChanged(x, y);
				break;
			}
			break;

			default:
			{
				return DefWindowProc(hWnd, msg, wParam, lParam);
			}
		}
	}

	wstring Component::getClassName()
	{
		return wstring(this->_className->begin(), this->_className->end());
	}

	HINSTANCE Component::getInstance()
	{
		return this->_hInstance;
	}

	HWND Component::getHandle()
	{
		return this->_hWnd;
	}

	Component* Component::getParent()
	{
		return this->_parent;
	}

	wstring Component::getTitle()
	{
		wstring retValue;

		if (this->getHandle() != NULL)
		{
			wchar_t buffer = GetWindowTextLength( this->getHandle() );

			if (GetWindowText(this->getHandle(), &buffer, 256) > 0)
			{
				retValue = wstring(&buffer);
			}
			else
			{
				retValue = L"";
			}
		}
		else
		{
			throw W32WRException("Component not initialized/created.");
		}

		return retValue;
	}

	void Component::setTitle(wchar_t* title)
	{
		if (this->getHandle() != NULL)
		{
			SetWindowText(this->getHandle(), title);
		}
		else
		{
			throw W32WRException("Component not initialized/created.");
		}
	}

	DoubleVector<long> Component::getPosition()
	{
		if (this->getHandle() != NULL)
		{
			RECT rect;

			if (GetClientRect(this->getHandle(), &rect))
			{
				MapWindowPoints(this->getHandle(), this->getParent()->getHandle(), (LPPOINT)&rect, 2);
				return DoubleVector<long>(rect.left, rect.top);
			}
			else
			{
				throw W32WRException("Invalid GetWindowRect() call.");
			}
		}
		else
		{
			throw W32WRException("Component not initialized/created.");
		}
	}

	void Component::setPosition(DoubleVector<long> pos)
	{
		if (this->getHandle() != NULL)
		{
			SetWindowPos(this->getHandle(), NULL, pos.getX(), pos.getY(), NULL, NULL, SWP_NOZORDER | SWP_NOSIZE);
		}
		else
		{
			throw W32WRException("Component not initialized/created.");
		}
	}

	DoubleVector<long> Component::getSize()
	{
		if (this->getHandle() != NULL)
		{
			RECT rect;

			if (GetWindowRect(this->getHandle(), &rect))
			{
				return DoubleVector<long>(rect.right - rect.left, rect.bottom - rect.top);
			}
			else
			{
				throw W32WRException("Invalid GetWindowRect() call.");
			}
		}
		else
		{
			throw W32WRException("Component not initialized/created.");
		}
	}

	void Component::setSize(DoubleVector<long> size)
	{
		if (this->getHandle() != NULL)
		{
			SetWindowPos(this->getHandle(), NULL, NULL, NULL, size.getX(), size.getY(), SWP_NOZORDER | SWP_NOMOVE);
		}
		else
		{
			throw W32WRException("Component not initialized/created.");
		}
	}

	void Component::createTimer(UINT_PTR identifier, UINT interval)
	{
		if (this->getHandle() != NULL)
		{
			if ( !SetTimer(this->getHandle(), identifier, interval, (TIMERPROC)NULL) )
			{
				throw W32WRException("Invalid SetTimer() Call.");
			}
		}
		else
		{
			throw W32WRException("Component not initialized/created.");
		}
	}

	void Component::destroyTimer(UINT_PTR identifier)
	{
		if (this->getHandle() != NULL)
		{
			if ( KillTimer(this->getHandle(), identifier) )
			{
				throw W32WRException("Invalid KillTimer() Call.");
			}
		}
		else
		{
			throw W32WRException("Component not initialized/created.");
		}
	}

}