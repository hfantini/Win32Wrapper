#pragma once
#include "../system/component.h"

using namespace std;

namespace Win32Wrapper
{
	class Control : public Component
	{
		public:

			Control(HINSTANCE hInstance, Component* parent, wstring className);
			~Control();

			virtual void show();
			virtual void hide();

		private:

			static LRESULT CALLBACK staticWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		protected:

			virtual void registerClass() override;
			void onCreate(HWND hWnd) override;
			void onDestroy(HWND hWnd) override;
			void onPositionChanged(UINT width, UINT height) override;
			void onSizeChanged(UINT type, UINT width, UINT height) override;
	};
}