#pragma once
#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include <stdlib.h>
#include <set>

namespace game_framework {
	template<class T>
	void Swap(T &lhs, T &rhs)
	{
		T temp = lhs;
		lhs = rhs;
		rhs = temp;
	}

	template<class T>
	T *FindSetFromOrder(set<T*>& lhs, int order)
	{
		int i = 0;
		for (set<T*>::iterator it = lhs.begin(); it != lhs.end(); ++it, ++i) {
			if (i == order) {
				return *it;
			}
		}
		return NULL;
	}
}