#include "stopFactoryEvent.h"

StopFactoryEvent::StopFactoryEvent(double timestamp, int factoryId) 
	: FactoryEvent{ timestamp,  factoryId }{};

void StopFactoryEvent::run() {
	
	State* state = State::getInstance();

	auto it = find_if(state->getStarvedFactories().begin(),
		state->getStarvedFactories().end(),
		[this](std::shared_ptr<Factory> f) {return f->getFactoryId() == this->getFactoryId(); });

	if (it != state->getStarvedFactories().end()) {
		state->getStoppedFactories().push_back(*it);
		state->getStarvedFactories().erase(it);
	}else{

		auto it = find_if(state->getRunningFactories().begin(),
			state->getRunningFactories().end(),
			[this](std::shared_ptr<Factory> f) {return f->getFactoryId() == this->getFactoryId(); });

		if (it != state->getRunningFactories().end()) {
			state->getStoppedFactories().push_back(*it);
			state->getRunningFactories().erase(it);
		}

	}

}