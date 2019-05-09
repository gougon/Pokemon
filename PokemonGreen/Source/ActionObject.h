#pragma once
#include <string>
#include <vector>
#include "GameObject.h"

using namespace std;
namespace game_framework
{
	class ActionObject : public GameObject
	{
		public:
			ActionObject();
			virtual void KeyDownListener(UINT nChar) = 0;
			virtual void RecieveData(int, int) {}
			void Start();
			void End();
			bool IsWork();
		protected:
			bool isWork = false;
	};
}

