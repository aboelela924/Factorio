#include "stopFactoryEvent.h"

StopFactoryEvent::StopFactoryEvent(double timestamp, int factoryId) 
	: FactoryEvent{ timestamp,  factoryId }{};

void StopFactoryEvent::run() {
	
}