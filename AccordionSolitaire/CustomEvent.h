#pragma once
#include "Enums.h"

class CustomEvent
{
public:
	CustomEventTypes type;
	int eventData;

	CustomEvent();
	CustomEvent(CustomEventTypes inType, int inEventData);
};

