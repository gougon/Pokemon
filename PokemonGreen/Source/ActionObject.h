#pragma once
#include <string>
#include <vector>

using namespace std;
namespace game_framework
{
	class ActionObject
	{
		public:
			ActionObject();
			virtual void Init() = 0;
			virtual void OnShow() = 0;
			virtual void OnMove() = 0;
			virtual void LoadBitmap() = 0;
			virtual void KeyDownListener(UINT nChar) = 0;
			virtual void RecieveData(int, int) {}
			void Start();
			void End();
			bool IsWork();
		protected:
			bool isWork = false;
	};
}

