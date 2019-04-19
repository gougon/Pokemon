#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CEvent.h"
namespace game_framework
{
CEvent::CEvent()
{
    for (int i = 0; i < EVENT_SIZE; i++)
    {
        event_list[i] = false;
    }
}
void CEvent::Occur(int EventID)
{
    event_list[EventID] = true;
}
bool CEvent::CheckOccured(int EventID)
{
    return event_list[EventID];
}
}