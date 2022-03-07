#pragma once

#include "event.h"
#include <iostream>

using namespace std;


class StopFactoryEvent : public Event {
private:
	int factoryId;

public:

	StopFactoryEvent(double timestamp, int factoryId);

	void run() override;

};