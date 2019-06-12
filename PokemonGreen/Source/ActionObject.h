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
		virtual ~ActionObject() {};
		virtual void Init() {}
		virtual void KeyDownListener(UINT nChar) = 0;
		virtual void RecieveItem(int, int) {}
		virtual void OnShow() = 0;
		virtual void OnMove() = 0;
		virtual void LoadBitmap() = 0;
		void Start();
		void End();
		bool IsWork();
	protected:
		bool isWork = false;
	};
}

