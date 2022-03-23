#pragma once

#include "event.h"
#include <iostream>

#include <string>

using namespace std;

class DestoryFactoryEvent : public Event {

private:
	int factoryId;

public:

	DestoryFactoryEvent(double timestamp, int factoryId);

	void run() override;

};