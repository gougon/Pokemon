#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CHero.h"
#include "CMap.h"

using namespace std;
namespace game_framework {
	CMap::CMap() :
		audioCounter(0)
	{
		// empty body
	}

	CMap::CMap(int sceneNum) :
		audioCounter(0)
	{
		scene = new CMovingBitmap[sceneNum];
	}

	CMap::~CMap()
	{
		delete[] scene;
	}

	void CMap::SetMXY(int mx, int my)
	{
		this->mx = mx;
		this->my = my;
	}

	void CMap::SetXY(int sx, int sy)
	{
		this->sx = sx;
		this->sy = sy;
	}

	void CMap::SetMap(string mapName)
	{
		this->map.clear(); //清空vector避免上一個map殘留
		fstream file;
		file.open(".\\Maptxts\\" + mapName + ".txt");

		if (!file.is_open())
			ASSERT(0);

		for (int i = 0; i < my; ++i)
		{
			vector<int> row;

			for (int j = 0; j < mx; ++j)
			{
				string data;
				file >> data;
				row.push_back(atoi(data.c_str()));
			}

			this->map.push_back(row);
		}

		file.close();
	}

	int CMap::GetSX()
	{
		return sx;
	}

	int CMap::GetSY()
	{
		return sy;
	}

	string CMap::GetName()
	{
		return name;
	}

	bool CMap::IsEntrance(int x, int y)
	{
		return (map[y / SM][x / SM] == ENTRANCE);
	}

	void CMap::SetTopLeft(int order, int x, int y)
	{
		scene[order].SetTopLeft(x, y);
		scene[order].ShowBitmap();
	}
}