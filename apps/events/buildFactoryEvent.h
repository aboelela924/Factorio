#pragma once


#include "event.h"
#include "../state.h"

#include <string>
#include <iostream>

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