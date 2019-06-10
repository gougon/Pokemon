#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CCharacter.h"
using namespace std;
namespace game_framework
{
CCharacter::CCharacter()
{
    //
}
CCharacter::CCharacter(int chaID)
{
    // if (chaID == 0)
    // {
    //     scene[0].LoadBitmap(MOM_UP, RGB(255, 0, 0));
    //     scene[1].LoadBitmap(MOM_DOWN, RGB(255, 0, 0));
    //     scene[2].LoadBitmap(MOM_LEFT, RGB(255, 0, 0));
    //     scene[3].LoadBitmap(MOM_RIGHT, RGB(255, 0, 0));
    // }
	// else if(chaID == 1)
	// {
	// 	scene[0].LoadBitmap(FATGUY_UP, RGB(255, 0, 0));
	// 	scene[1].LoadBitmap(FATGUY_DOWN, RGB(255, 0, 0));
	// 	scene[2].LoadBitmap(FATGUY_LEFT, RGB(255, 0, 0));
	// 	scene[3].LoadBitmap(FATGUY_RIGHT, RGB(255, 0, 0));
	// }
}
// CMovingBitmap* CCharacter::setCharacter(int chaID)
// {
// 	   character_scene_pointer = scene;
//     return character_scene_pointer;
// }
}
