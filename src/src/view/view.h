#pragma once
#include "../system/component.h"

using namespace std;

namespace Win32Wrapper
{
	class View : public Component
	{
		public:

			View(HINSTANCE hInstance, Component* parent, wstring className);
			virtual ~View();

			virtual void create() override;

			virtual void show(int nCmdShow);
			virtual void show();
			virtual void hide();

		private:

			static LRESULT CALLBACK staticWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		protected:

			virtual void registerClass() override;
			void onCreate(HWND hWnd) override;
			void onDestroy(HWND hWnd) override;
	};
}