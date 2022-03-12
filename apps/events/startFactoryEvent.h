#pragma once

#include "factoryEvent.h"
#include "../state.h"
#include "../feedback.h"

#include <iostream>
#include <string>
#include <memory>
#include <cmath>

using namespace std;

class StartFactoryEvent : public FactoryEvent {

private:
	string recipe;
	Feedback* feedback;

public:

	StartFactoryEvent(Feedback* feedback, double timestamp, int factoryId, string recipe);

	void run() override;

	std::string getRecipeName();
	bool isFactoryStillRunning(double currentTick, int energy, double craftingSpeed);
	bool isDone(double currentTick, int energy, double craftingSpeed);
	void setStartingTimeStamp(double tick);
};