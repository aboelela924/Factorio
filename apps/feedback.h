#pragma once
#include <map>
#include <vector>
#include <unordered_set>
#include "events/factoryEvent.h"

class Feedback {
public:
	Feedback();
	virtual void eventDone(FactoryEvent* e) = 0;
	std::unordered_set<std::string> eventsSet;
};