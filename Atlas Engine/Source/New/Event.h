#pragma once

enum class EventCategory
{
	None = 0,
	Mouse, Keyboard, Window
};

namespace Atlas {
	class Event {
	private:

	public:
		Event();
		virtual ~Event();
	};
}