#pragma once
#define EVENT_SIZE 10
enum DialogState {
	Start,
	Continue,
	End
};
namespace game_framework
{
class CEvent
{
    public:
        CEvent();
        void Occur(int EventID);
        bool CheckOccured(int EventID);
    private:
        bool event_list[EVENT_SIZE];
};
}
