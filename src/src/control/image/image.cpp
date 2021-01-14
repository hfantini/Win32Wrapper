#include "image.h"

namespace Win32Wrapper
{
	Image::Image(HINSTANCE hInstance, Component* parent, wstring source) : Control(hInstance, parent, L"W32WR_IMAGE")
	{
		Control::registerClass();
		this->setSource(source);
	}

	Image::~Image()
	{
		if (this->_source)
		{
			delete this->_source;
		}
	}

	void Image::create()
	{
		if (this->getHandle() == NULL)
		{
			HWND hWndParent = NULL;

			if (this->getParent() != NULL)
			{
				hWndParent = this->getParent()->getHandle();
			}

			this->_hWnd = CreateWindow(
				this->_className->c_str(),
				L"IMAGE",
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				0,
				0,
				200,
				200,
				hWndParent,
				NULL,
				this->getParent()->getInstance(),
				this);
		}
		else
		{
			throw W32WRException("Control already been created");
		}
	}

	void Image::onCreate(HWND hWnd)
	{
		loadImageFromSource();
	}

	void Image::loadImageFromSource()
	{
		if (!this->_source->empty())
		{
			this->_hbitmapSource = (HBITMAP)LoadImage(this->getInstance(), this->_source->c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
	}

	void Image::onDestroy(HWND hWnd)
	{
		if (this->_source)
		{
			DeleteObject(this->_source);
		}
	}

	void Image::onPaint()
	{
		if (this->_hbitmapSource)
		{
			BITMAP bm;
			PAINTSTRUCT ps;

			HDC hdc = BeginPaint(this->getHandle(), &ps);

			HDC hdcMem = CreateCompatibleDC(hdc);
			HGDIOBJ hbmOld = SelectObject(hdcMem, this->_hbitmapSource);

			GetObject(this->_hbitmapSource, sizeof(bm), &bm);

			DoubleVector<long> size = this->getSize();

			BitBlt(hdc, 0, 0, size.getX(), size.getY(), hdcMem, 0, 0, SRCCOPY);

			SelectObject(hdcMem, hbmOld);
			DeleteDC(hdcMem);

			EndPaint(this->getHandle(), &ps);
		}
	}

	wstring Image::getSource()
	{
		return wstring(this->_source->begin(), this->_source->end());
	}

	void Image::setSource(wstring source)
	{
		if (this->_source)
		{
			delete this->_source;
		}

		this->_source = new wstring(source);
	}
}