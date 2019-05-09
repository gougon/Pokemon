#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CHero.h"
#include "CMap.h"

using namespace std;
namespace game_framework
{
CMap::CMap()
{
    /*empty body*/
}

CMap::CMap(int sceneNum)
{
    scene = new CMovingBitmap[sceneNum];
}

void CMap::SetMXY(int mx, int my)
{
    this->mx = mx;
    this->my = my;
	TRACE("\nmx = %d, my = %d\n", mx, my);
}

void CMap::SetXY(int sx, int sy)
{
    this->sx = sx;
    this->sy = sy;
	TRACE("\nsx = %d, sy = %d\n", sx, sy);
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