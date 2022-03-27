#pragma once
#include "event.h"

class  FactoryEvent : public Event {
protected:
	int factoryId;
public:
	FactoryEvent(double timestamp, int factoryId);
	virtual void run() = 0;

	int getFactoryId();
};
