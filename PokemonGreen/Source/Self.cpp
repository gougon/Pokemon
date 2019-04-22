#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Self.h"

namespace game_framework
{
void Self::Init()
{
}

void Self::OnShow()
{
    self_image.ShowBitmap();
}

void Self::OnMove()
{
}

void Self::LoadBitmap()
{
    self_image.LoadBitmap(BG_SELF);
    self_image.SetTopLeft(0, 0);
}

void Self::KeyDownListener(UINT nChar)
{
    const char KEY_Z = 0x5a;
    const char KEY_X = 0x58;

    if (nChar == KEY_X || nChar == KEY_Z)
    {
        End();
    }
}
}