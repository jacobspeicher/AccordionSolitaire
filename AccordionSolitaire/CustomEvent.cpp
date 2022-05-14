#include "CustomEvent.h"

CustomEvent::CustomEvent()
{
	screen = Screen::null;
	event = 0;
}

CustomEvent::CustomEvent(Screen inScreen, int inEvent)
{
	screen = inScreen;
	event = inEvent;
}

CustomEvent::CustomEvent(Screen inScreen, int inEvent, std::map<std::string, int> inData)
{
	screen = inScreen;
	event = inEvent;
	data = inData;
}