#include "buildFactoryEvent.h"



BuildFactoryEvent::BuildFactoryEvent(double timestamp, int factoryId, string factoryType, string factoryName)
	: Event{ timestamp }, factoryId(factoryId), factoryType(factoryType), factoryName(factoryName) {};

void BuildFactoryEvent::run() {
	cout << "Build Factory id: " << factoryId << ", Factory type: " << factoryType
		<< "Factory name: " << factoryName << " and timestamp: " << this->getTimestamp() << endl;

	State* state = State::getInstance();
	std::shared_ptr<Factory> f;

	auto it = find_if(state->getNotStartedFactories().begin(),
		state->getNotStartedFactories().end(),
		[this](std::shared_ptr<Factory> obj) {return obj->getName() == this->factoryName; });

	if (it != state->getNotStartedFactories().end()) {
		
		auto index = std::distance(state->getNotStartedFactories().begin(), it);
		f = state->getNotStartedFactories()[index];
		state->getNotStartedFactories().erase(state->getNotStartedFactories().begin() + index);
		
	}
	else {
		
	}
}
