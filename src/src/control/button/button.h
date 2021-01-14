#pragma once
#include "../../../pch.h"
#include "../control.h"
#include "../../exception/W32WRException.h"

namespace Win32Wrapper
{
	class Button : public Control
	{
		public:

			Button(HINSTANCE hInstance, Component* parent);
			~Button();

			virtual void registerClass() override;
			virtual void unregisterClass() override;
			virtual void create() override;

		private:
		protected:

			void onCreate(HWND hWnd) override;
	};
}