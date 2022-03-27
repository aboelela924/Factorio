#include "factoryEvent.h"

FactoryEvent::FactoryEvent(double timestamp, int factoryId) : Event{timestamp}, factoryId(factoryId)
{
}

int FactoryEvent::getFactoryId()
{
	return this->factoryId;
}
