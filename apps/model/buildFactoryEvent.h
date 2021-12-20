#pragma once


#include "event.h"
#include <string>

using namespace std;


class BuildFactoryEvent : public Event {

private:
	int factoryId;
	string factoryType;
	string factoryName;

public:

	BuildFactoryEvent(double timestamp, int factoryId, string factoryType, string factoryName);

	void run() override;

};