#pragma once
#include "button.h"


namespace Win32Wrapper
{
	Button::Button(HINSTANCE hInstance, Component* parent) : Control( hInstance, parent, wstring(L"BUTTON") )
	{

	}

	Button::~Button()
	{

	}

	void Button::registerClass()
	{

	}

	void Button::unregisterClass()
	{

	}

	void Button::create()
	{
		if (this->getHandle() == NULL)
		{
			HWND hWndParent = NULL;

			if (this->getParent() != NULL)
			{
				hWndParent = this->getParent()->getHandle();
			}

			this->_hWnd = CreateWindow(
				L"BUTTON",
				L"BUTTON",
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				0,
				0,
				200,
				40,
				hWndParent,
				NULL, 
				this->getParent()->getInstance(),
				NULL);
		}
		else
		{
			throw W32WRException("Control already been created");
		}
	}

	void Button::onCreate(HWND hWnd)
	{
		this->setTitle((wchar_t*)L"BUTTON");
	}
}