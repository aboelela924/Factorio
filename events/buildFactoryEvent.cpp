#include "buildFactoryEvent.h"



BuildFactoryEvent::BuildFactoryEvent(double timestamp, int factoryId, string factoryType, string factoryName)
	: FactoryEvent{ timestamp, factoryId }, factoryType(factoryType), factoryName(factoryName) {};

void BuildFactoryEvent::run() {
	cout << "Build Factory id: " << factoryId << ", Factory type: " << factoryType
		<< "Factory name: " << factoryName << " and timestamp: " << this->getTimestamp() << endl;

	State* state = State::getInstance();
	/*Factory f = state->getFactoryByName(factoryName);
	f.setFactoryId(this->factoryId);
	f.setFactoryType(this->factoryType);
	state->addBuiltFactories(f);*/

	
}
