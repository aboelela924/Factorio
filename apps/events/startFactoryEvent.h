#pragma once

#include "factoryEvent.h"
#include "../state.h"

#include <iostream>
#include <string>
#include <memory>

using namespace std;

class StartFactoryEvent : public FactoryEvent {

private:
	string recipe;
	double timeRequired;

public:

	StartFactoryEvent(double timestamp, int factoryId, string recipe);

	void run() override;

	bool isFactoryStillRunning();

};