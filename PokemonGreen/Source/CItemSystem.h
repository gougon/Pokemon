#pragma once
namespace game_framework
{
	class CItemSystem {
	public:
		string GetNameByID(int ID);
		int GetIDByName(string name);
	};
}