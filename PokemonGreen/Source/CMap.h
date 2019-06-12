#ifndef CMAP
#define CMAP

#include <vector>
#include <string>
#include <fstream>
#include "CDialog.h"
#include "CCharacter.h"
#include "AtkInterface.h"
#include "CEvent.h"
using namespace std;
constexpr auto X = 11;
constexpr auto Y = 8;
constexpr auto EXPEND = 9;
constexpr auto SM = 60;

constexpr auto NONE_HIT = 0;
constexpr auto NONE_EMPTY = 1;
constexpr auto ENTRANCE = -1;
constexpr auto HOSPITAL = 13;
constexpr auto STORE = 14;

constexpr auto SHOP_MAP = 2;
constexpr auto HOSPITAL_INSIDE = 2;
constexpr auto NURSE = 3;

enum mapID
{
    weibaitown, // 0
    weibai_1_1f // 1
};
namespace game_framework
{
class CHero;
class AtkInterface;
class Pokemon;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲地圖物件
/////////////////////////////////////////////////////////////////////////////

class CMap
{
    public:
        CMap();
		virtual ~CMap() { delete[] scene; };
        CMap(int sceneNum);
        virtual void InitMap() {}
        virtual void LoadBitmap() {}
        void SetMXY(int mx, int my);
        void SetXY(int sx, int sy);
        void SetMap(string mapName);
        int GetSX();
        int GetSY();
		string GetName();
        virtual void OnMove() {}
        virtual void OnShow() {}
		virtual void ReShow(CHero &hero) {}
        virtual bool IsCollision(int x, int y, CHero &hero) { return true; }
        bool IsEntrance(int x, int y);
		virtual void KeyDownListener(UINT nChar, CHero &hero) {}
        virtual int ReturnMapID() { return 0; }
        virtual bool IsWarZone(int x, int y) { return false; }		// for derive class
		virtual bool IsJumpLand(int x, int y, CHero &hero) { return false; }
		virtual void ProduceEnemy(CHero* hero, AtkInterface &atkInterface) { /* empty body */ }
        virtual CMap* ChangeMap(int x, int y, CHero* hero) { return new CMap(); }     // for derive class 
        virtual void StartAtk(CHero* self, Pokemon* enemy, AtkInterface &atkInterface) { /* empty body */ }
        virtual void StartAtk(CHero* self, CCharacter* enemy, AtkInterface &atkInterface) { /* empty body */ }
    protected:
		void SetTopLeft(int order, int x, int y);
		string name;
        CEvent* mapGameEvent;
        CMovingBitmap* scene;
        vector<vector<int> > map;
		int audioCounter = 0;
    private:
        int sx, sy;				// pixel
        int mx, my;				// 格
};
}

#endif