#pragma once
#include "../../../pch.h"
#include "../control.h"
#include "../../exception/W32WRException.h"

namespace Win32Wrapper
{
	class Image : public Control
	{
		public:

			Image(HINSTANCE hInstance, Component* parent, wstring source);
			~Image();

			virtual void create() override;

			wstring getSource();
			void setSource(wstring source);

		private:

			wstring* _source;
			void loadImageFromSource();

		protected:

			HBITMAP _hbitmapSource;

			void onCreate(HWND hWnd) override;
			void onDestroy(HWND hWnd) override;
			void onPaint() override;
	};
}