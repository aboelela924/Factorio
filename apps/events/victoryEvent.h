#pragma once

#include "event.h"
#include <iostream>

using namespace std;

class VictoryEvent : public Event {

public:
	VictoryEvent(double timestamp);

	void run() override;

};
