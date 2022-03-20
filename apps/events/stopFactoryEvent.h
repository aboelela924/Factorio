#pragma once

#include "factoryEvent.h"
#include "../state.h"
#include <iostream>

using namespace std;


class StopFactoryEvent : public FactoryEvent {
private:
	

public:

	StopFactoryEvent(double timestamp, int factoryId);

	void run() override;

};