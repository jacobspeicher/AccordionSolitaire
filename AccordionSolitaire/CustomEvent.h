#pragma once
#include "Enums.h"

class CustomEvent
{
public:
	Screen screen;
	int eventData;

	CustomEvent();
	CustomEvent(Screen inScreen, int inEventData);
};

