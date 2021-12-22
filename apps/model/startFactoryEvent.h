#pragma once

#include "event.h"
#include <iostream>
#include <string>

using namespace std;

class StartFactoryEvent : public Event {

private:
	int factoryId; 
	string recipe;

public:

	StartFactoryEvent(double timestamp, int factoryId, string recipe);

	void run() override;

};