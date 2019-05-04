#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "GameObject.h"

namespace game_framework {
	GameObject::GameObject() :
		layer(0)
	{
		// empty body
	}

	void GameObject::SetLayer(int layer)
	{
		this->layer = layer;
	}

	int GameObject::GetLayer()
	{
		return layer;
	}
}