#pragma once
#include "../../pch.h"

namespace Win32Wrapper
{
	template <typename T>
	class DoubleVector
	{
		public:

			DoubleVector(T x, T y)
			{
				this->_x = x;
				this->_y = y;
			}

			~DoubleVector() 
			{

			};

			T getX()
			{
				return this->_x;
			}

			void setX(T x)
			{
				this->_x = x;
			}

			T getY()
			{
				return this->_y;
			}
			void setY(T y)
			{
				this->_y = y;
			}

		private:
		protected:

			T _x;
			T _y;
	};
}
