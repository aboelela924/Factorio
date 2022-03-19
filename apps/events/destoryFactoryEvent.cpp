#include  "destoryFactoryEvent.h"

DestoryFactoryEvent::DestoryFactoryEvent(double timestamp, int factoryId)
	: Event{ timestamp }, factoryId(factoryId){};

void DestoryFactoryEvent::run() {
	
	State* state = State::getInstance();

	state->getFactoryById(factoryId);

}