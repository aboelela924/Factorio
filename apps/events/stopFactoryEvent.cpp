#include "stopFactoryEvent.h"
#include <nlohmann/json.hpp>
#include <iomanip>


StopFactoryEvent::StopFactoryEvent(double timestamp, int factoryId) 
	: FactoryEvent{ timestamp,  factoryId }{};

void StopFactoryEvent::run() {
	// cout << "Start factory event with factory id: " << factoryId << ", timestamp: " << this->getTimestamp() << endl;
	vector<string> event={"4",to_string(this->getTimestamp()),to_string(factoryId)};
	
	JsonParser::testFunction(event);
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
