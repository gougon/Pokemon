#pragma once
#define EVENT_SIZE 10

namespace game_framework {
	enum DialogState {
		Start,
		Continue,
		End
	};

	class CEvent {
	public:
		CEvent();
		void Occur(int EventID);
		bool CheckOccured(int EventID);
	private:
		bool event_list[EVENT_SIZE];
	};
}
