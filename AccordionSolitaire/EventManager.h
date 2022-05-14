#pragma once
#include <map>
#include <vector>
#include <cassert>
#include "CustomEvent.h"

class EventManager
{
public:
	static void init()
	{
		head = 0;
		tail = 0;
	}

	// add an event to the queue
	static void QueueEvent(CustomEvent event)
	{
		assert((tail + 1) % MAX_PENDING != head);

		queue[tail] = event;
		tail = (tail + 1) % MAX_PENDING;
	}

	// get the oldest event
	static CustomEvent DequeueEvent()
	{
		if (head == tail) return CustomEvent();

		CustomEvent returnedEvent = queue[head];
		head = (head + 1) % MAX_PENDING;
		return returnedEvent;
	}

private:
	const static int MAX_PENDING = 10;

	static int head;
	static int tail;
	static CustomEvent queue[MAX_PENDING];
};

