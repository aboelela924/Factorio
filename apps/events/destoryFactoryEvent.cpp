#include  "destoryFactoryEvent.h"
#include <nlohmann/json.hpp>
#include <iomanip>

DestoryFactoryEvent::DestoryFactoryEvent(double timestamp, int factoryId)
	: Event{ timestamp }, factoryId(factoryId){};

void DestoryFactoryEvent::run() {

	vector<string> event={"3",to_string(this->getTimestamp()),to_string(factoryId)};
	JsonParser::testFunction(event);
	
	State* state = State::getInstance();

	auto stoppedFactories = state->getStoppedFactories();
	int factoryId = this->factoryId;

	auto it = find_if(stoppedFactories.begin(),
		stoppedFactories.end(), 
		[factoryId](std::shared_ptr<Factory> f) {return f->getFactoryId() == factoryId; });

	stoppedFactories.erase(it);

	state->addFactoryIdToIdPool(factoryId);

}