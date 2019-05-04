#pragma once
#include <string>
#include <vector>

using namespace std;
namespace game_framework
{
	class GameObject
	{
	public:
		GameObject();
		virtual void Init() = 0;
		virtual void OnMove() = 0;
		virtual void OnShow() = 0;
		virtual void LoadBitmap() = 0;
		virtual void SetTopLeft() = 0;
		void SetLayer(int layer);
		int GetLayer();
	protected:
	private:
		int layer;
	};
}