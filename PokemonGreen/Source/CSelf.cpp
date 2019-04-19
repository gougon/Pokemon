#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <string>
#include "CSelf.h"
using namespace std;
namespace game_framework
{
CSelf::CSelf()
{
}
void CSelf::LoadBitmap()
{
    self_image.LoadBitmap(BG_SELF);
    self_image.SetTopLeft(0, 0);
}
void CSelf::OnShow()
{
    self_image.ShowBitmap();
}
}
