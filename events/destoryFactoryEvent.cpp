#include  "destoryFactoryEvent.h"

DestoryFactoryEvent::DestoryFactoryEvent(double timestamp, int factoryId)
	: Event{ timestamp }, factoryId(factoryId){};

void DestoryFactoryEvent::run() {
	
	State* state = State::getInstance();

	auto stoppedFactories = state->getStoppedFactories();
	int factoryId = this->factoryId;

	auto it = find_if(stoppedFactories.begin(),
		stoppedFactories.end(), 
		[factoryId](std::shared_ptr<Factory> f) {return f->getFactoryId() == factoryId; });

	stoppedFactories.erase(it);

	state->addFactoryIdToIdPool(factoryId);

}