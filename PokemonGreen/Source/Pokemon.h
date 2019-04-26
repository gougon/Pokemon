#pragma once

#include <string>
#include <vector>
#include "Skill.h"
<<<<<<< HEAD
#include "CItem.h"
=======
#include "PmValue.h"
#include "CPickableObject.h"
>>>>>>> 9c1c6bf5c624e9a0e003821a8ec7d41fcb3499b7

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

<<<<<<< HEAD
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
        void AddExp(Pokemon* enemy);
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
        virtual bool HaveItem()
        {
            return haveItem;
        }
        int exp[30] =  														// �]�w�g��ȹD30��
        {
            6, 15, 30, 49, 72, 102, 135, 174, 217, 264,
            318, 374, 438, 505, 576, 654, 735, 822, 913, 1008,
            1110, 1215, 1326, 1441, 1560, 1686, 1815, 1950, 2089, 2232
        };
    protected:
        class PmValue
        {
            public:
                PmValue();
                PmValue(int hp, int atk, int def, int sa, int sd, int sp);
                void SetAll(int hp, int sp, int atk, int def, int sa, int sd);
                int hp;
                int speed, atk, def, satk, sdef;
        };
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
        //take item
        bool haveItem;
        int takeItemID;
};
=======
	class Pokemon {
	public:
		Pokemon();
		virtual void Init(string Name) = 0;
		void OnShow();
		void OnShow(string);
		Attribute GetAttribute();
		virtual void LoadBitmap() = 0;
		void LoadValue();
		void AddSkill(Skill *skill);
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
		Skill *GetSkill(int order);
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
		void SetItem(CPickableObject *item);
		void UseItem(CPickableObject *item);

		int exp[30] = {														// �]�w�g��ȹD30��
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
		CPickableObject *item;
	};
>>>>>>> 9c1c6bf5c624e9a0e003821a8ec7d41fcb3499b7
}