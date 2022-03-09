#pragma once

#include "factoryEvent.h"
#include "../state.h"

#include <iostream>
#include <string>
#include <memory>
#include <cmath>

using namespace std;

class StartFactoryEvent : public FactoryEvent {

private:
	string recipe;

public:

	StartFactoryEvent(double timestamp, int factoryId, string recipe);

	void run() override;

	bool isFactoryStillRunning(double currentTick, double timeRequired);

};