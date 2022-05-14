#pragma once
#include "Enums.h"
#include <map>
#include <string>

class CustomEvent
{
public:
	Screen screen;
	int event;
	std::map<std::string, int> data;

	CustomEvent();
	CustomEvent(Screen inScreen, int inEvent);
	CustomEvent(Screen inScreen, int inEvent, std::map<std::string, int> inData);
};

