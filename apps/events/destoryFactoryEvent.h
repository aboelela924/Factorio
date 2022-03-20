#pragma once

#include "event.h"
#include <iostream>
#include "../state.h"

class DestoryFactoryEvent : public Event {

private:
	int factoryId;

public:

	DestoryFactoryEvent(double timestamp, int factoryId);

	void run() override;

};