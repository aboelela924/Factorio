#pragma once
#include "events/factoryEvent.h"

class Feedback {
public:
	virtual void eventDone(FactoryEvent& event) = 0;
}