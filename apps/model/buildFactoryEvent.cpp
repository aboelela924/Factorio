#include <iostream>
#include "buildFactoryEvent.h"



BuildFactoryEvent::BuildFactoryEvent(double timestamp, int factoryId, string factoryType, string factoryName)
	: Event{ timestamp }, factoryId(factoryId), factoryType(factoryType), factoryName(factoryName) {};

void BuildFactoryEvent::run() {
	cout << "Build Factory id: " << factoryId << ", Factory type: " << factoryType
		<< "Factory name: " << factoryName << " and timestamp: " << this->getTimestamp() << endl;
}
