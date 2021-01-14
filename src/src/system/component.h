#pragma once
#include "../../pch.h"
#include "../exception/W32WRException.h"
#include "../exception/ExceptionHandler.h"
#include "../structure/DoubleVector.h"

using namespace std;

namespace Win32Wrapper
{
	class Component
	{
		public:

			Component(HINSTANCE hInstance, Component* parent);
			virtual ~Component();

			wstring getClassName();

			virtual void create();
			virtual void destroy();
			HWND getHandle();
			HINSTANCE getInstance();
			Component* getParent();
			virtual LRESULT CALLBACK windowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
			void dispatchException(W32WRException e);

			wstring getTitle();
			void setTitle(wchar_t* title);
			virtual DoubleVector<long> getPosition();
			virtual void setPosition(DoubleVector<long> pos);
			virtual DoubleVector<long> getSize();
			virtual void setSize(DoubleVector<long> pos);

		private:

			Component* _parent;
			HINSTANCE _hInstance;

		protected:

			HWND _hWnd;
			wstring* _className;

			virtual void registerClass();
			virtual void unregisterClass();

			virtual void createTimer(UINT_PTR identifier, UINT interval);
			virtual void destroyTimer(UINT_PTR identifier);

			virtual void onCreate(HWND hWnd);
			virtual void onDestroy(HWND hWnd);
			virtual void onPaint();
			virtual void onPositionChanged(UINT posX, UINT posY);
			virtual void onSizeChanged(UINT type, UINT width, UINT height);
			virtual void onTimerTick(UINT_PTR identifier);
	};
}