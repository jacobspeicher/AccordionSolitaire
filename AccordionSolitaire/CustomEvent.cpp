#include "CustomEvent.h"

CustomEvent::CustomEvent()
{
	type = CustomEventTypes::null;
	eventData = 0;
}

CustomEvent::CustomEvent(CustomEventTypes inType, int inEventData)
{
	type = inType;
	eventData = inEventData;
}