#include "CustomEvent.h"

CustomEvent::CustomEvent()
{
	screen = Screen::null;
	eventData = 0;
}

CustomEvent::CustomEvent(Screen inScreen, int inEventData)
{
	screen = inScreen;
	eventData = inEventData;
}