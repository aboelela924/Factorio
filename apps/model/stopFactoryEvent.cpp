#include "stopFactoryEvent.h"

StopFactoryEvent::StopFactoryEvent(double timestamp, int factoryId) 
	: Event{ timestamp }, factoryId(factoryId){};

void StopFactoryEvent::run() {
	cout << "Start factory event with factory id: " << factoryId
		<< ", timestamp: " << this->getTimestamp() << endl;
}