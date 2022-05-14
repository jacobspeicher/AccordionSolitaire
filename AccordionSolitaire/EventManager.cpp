#include "EventManager.h"

int EventManager::head = 0;
int EventManager::tail = 0;
CustomEvent EventManager::queue[MAX_PENDING];