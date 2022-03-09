#include "buildFactoryEvent.h"



BuildFactoryEvent::BuildFactoryEvent(double timestamp, int factoryId, string factoryType, string factoryName)
	: FactoryEvent{ timestamp, factoryId }, factoryType(factoryType), factoryName(factoryName) {};

void BuildFactoryEvent::run() {
	cout << "Build Factory id: " << factoryId << ", Factory type: " << factoryType
		<< "Factory name: " << factoryName << " and timestamp: " << this->getTimestamp() << endl;

	State* state = State::getInstance();
	std::shared_ptr<Factory> f;

	auto it = find_if(state->getBuiltFactories().begin(),
		state->getBuiltFactories().end(),
		[this](std::shared_ptr<Factory> obj) {return obj->getName() == this->factoryName; });

	if (it != state->getBuiltFactories().end()) {
		
		auto index = std::distance(state->getBuiltFactories().begin(), it);
		f = state->getBuiltFactories()[index];
		state->getBuiltFactories().erase(state->getBuiltFactories().begin() + index);
		
	}
	else {
		
	}
}
