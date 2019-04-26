#pragma once

#include <string>
#include <vector>
#include "Skill.h"
#include "PmValue.h"
#include "CPickableObject.h"
#include "CItem.h"

using namespace std;
namespace game_framework
{
class Skill;

enum PmType
{
    my, enemy
};

enum Attribute
{
    normal, fighting, flying, poison,
    ground, rock, bug, ghost, steel,
    fire, water, grass, electric,
    psychic, ice, dragon, dark
};

class Pokemon
{
    public:
        Pokemon();
        virtual void Init(string Name) = 0;
        void OnShow();
        void OnShow(string);
        Attribute GetAttribute();
        virtual void LoadBitmap() = 0;
        void LoadValue();
        void AddSkill(Skill* skill);
        bool AddExp(int addExp);
        void HpAnime();
        string GetName();
        int GetLevel();
        int GetHP();
        int GetSpeed();
        int GetAtk();
        int GetDef();
        int GetSatk();
        int GetSdef();
        float GetHitRate();
        float GetEvasionRate();
        int GetRemainHP();
        int GetNowExp();
        int GetNeedExp();
        int GetBasicExp();
        Skill* GetSkill(int order);
        int GetSkillNum();
        int GetHeight();
        CMovingBitmap GetIcon();
        CMovingBitmap GetFrontImage();
        int Left();
        int Top();
        void SetHP(int hp);
        void SetLevel(int lv);
        void SetRemainHP(int hp);
        void SetNowExp(int exp);
        void SetNeedExp(int exp);
        void SetTopLeft(int left, int top);
        void SetHeight(int height);
        bool UseItem(int itemID);
        bool TakeItem(int itemID);

        int exp[30] =  														// 設定經驗值道30等
        {
            6, 15, 30, 49, 72, 102, 135, 174, 217, 264,
            318, 374, 438, 505, 576, 654, 735, 822, 913, 1008,
            1110, 1215, 1326, 1441, 1560, 1686, 1815, 1950, 2089, 2232
        };
    protected:
        PmType pmtype;
        int remainhp;
        string name;
        Attribute attribute;
        int level;
        PmValue speciesStrength, individualValue, effortValue, mixValue;
        float hitRate, evasionRate;
        int nowExp, needExp, basicExp;
        vector<Skill*> skills;
        CMovingBitmap frontImg, backImg, icon;
        //CPickableObject *item;
        bool haveItem;
        int takeItemID;
};
}