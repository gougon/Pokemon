#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Pokemon.h"

namespace game_framework {
	// Pmvalue

	Pokemon::PmValue::PmValue()
		: hp(0), speed(0), atk(0), def(0), satk(0), sdef(0)
	{
		/* empty body */
	}

	Pokemon::PmValue::PmValue(int hp, int sp, int atk, int def, int sa, int sd)
		: hp(hp), speed(sp), atk(atk), def(def), satk(sa), sdef(sd)
	{
		/* empty body */
	}

	void Pokemon::PmValue::SetAll(int hp, int atk, int def, int sa, int sd, int sp)
	{
		this->hp = hp;
		this->atk = atk;
		this->def = def;
		this->satk = sa;
		this->sdef = sd;
		this->speed = sp;
	}

	// Pokemon

	Pokemon::Pokemon()
	{
		/* empty body */
	}

	void Pokemon::OnShow()
	{
		image.ShowBitmap();
	}

	void Pokemon::OnShow(string msg)
	{
		image.ShowBitmap("atk");
	}

	// Getter

	Attribute Pokemon::GetAttribute()
	{
		return attribute;
	}

	void Pokemon::LoadValue()
	{
		mixValue.hp = (level * (speciesStrength.hp + individualValue.hp) / 50) +
			((level * effortValue.hp / 100)) + 10 + level;
		mixValue.speed = (level * (speciesStrength.speed + individualValue.speed) / 50) +
			((level * effortValue.speed / 100)) + 5;
		mixValue.atk = (level * (speciesStrength.atk + individualValue.atk) / 50) +
			((level * effortValue.atk / 100)) + 5;
		mixValue.def = (level * (speciesStrength.def + individualValue.def) / 50) +
			((level * effortValue.def / 100)) + 5;
		mixValue.satk = (level * (speciesStrength.satk + individualValue.satk) / 50) +
			((level * effortValue.satk / 100)) + 5;
		mixValue.sdef = (level * (speciesStrength.sdef + individualValue.sdef) / 50) +
			((level * effortValue.sdef / 100)) + 5;
		remainhp = mixValue.hp;
	}

	void Pokemon::AddSkill(Skill *skill)
	{
		if(skills.size() < 4){
			skills.push_back(skill);
			// 跑對話說學習技能
		}
		else {
			// 詢問是否要覆蓋技能
		}
	}

	void Pokemon::AddExp(Pokemon *enemy)
	{
		nowExp += enemy->GetBasicExp() * enemy->GetLevel() / 7;
		/* if (nowExp > needExp) {
			nowExp -= needExp;
			level += 1;
			needExp = exp[level];
			LoadValue();
		} */
	}

	void Pokemon::HpAnime()
	{

	}

	string Pokemon::GetName()
	{
		return name;
	}

	int Pokemon::GetLevel()
	{
		return level;
	}

	int Pokemon::GetHP()
	{
		return mixValue.hp;
	}

	int Pokemon::GetSpeed()
	{
		return mixValue.speed;
	}

	int Pokemon::GetAtk()
	{
		return mixValue.atk;
	}

	int Pokemon::GetDef()
	{
		return mixValue.def;
	}

	int Pokemon::GetSatk()
	{
		return mixValue.atk;
	}

	int Pokemon::GetSdef()
	{
		return mixValue.sdef;
	}

	float Pokemon::GetHitRate()
	{
		return hitRate;
	}

	float Pokemon::GetEvasionRate()
	{
		return evasionRate;
	}

	int Pokemon::GetRemainHP()
	{
		return remainhp;
	}

	int Pokemon::GetNowExp()
	{
		return nowExp;
	}

	int Pokemon::GetNeedExp()
	{
		return needExp;
	}

	int Pokemon::GetBasicExp()
	{
		return basicExp;
	}

	Skill *Pokemon::GetSkill(int order)
	{
		if (order < (int)skills.size())
			return skills[order];
		else {
			ASSERT(0);
			return nullptr;
		}
	}

	int Pokemon::GetSkillNum()
	{
		return skills.size();
	}

	int Pokemon::GetHeight()
	{
		return image.RectHeight();
	}

	int Pokemon::Left()
	{
		return image.Left();
	}

	int Pokemon::Top()
	{
		return image.Top();
	}

	// Setter

	void Pokemon::SetHP(int hp)
	{
		mixValue.hp = hp;
		LoadValue();
	}

	void Pokemon::SetLevel(int lv)
	{
		level = lv;
		needExp = exp[level];
		LoadValue();
	}

	void Pokemon::SetRemainHP(int hp)
	{
		remainhp = hp;
	}

	void Pokemon::SetNowExp(int exp)
	{
		nowExp = exp;
	}

	void Pokemon::SetNeedExp(int exp)
	{
		needExp = exp;
	}

	void Pokemon::SetTopLeft(int left, int top)
	{
		image.SetTopLeft(left, top);
	}

	void Pokemon::SetHeight(int height)
	{
		image.SetHeight(height);
	}
}