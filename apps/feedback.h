#pragma once
#include <map>
#include <vector>
#include <unordered_set>
#include "events/factoryEvent.h"

class Feedback {
public:
	Feedback();
	std::map<int, std::vector<double>> factoryTimeMapping;
	std::unordered_set<int> runningProjectIds;
	virtual void eventDone(FactoryEvent* e) = 0;
};