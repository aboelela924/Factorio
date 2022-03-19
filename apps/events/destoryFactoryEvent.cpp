#include  "destoryFactoryEvent.h"

DestoryFactoryEvent::DestoryFactoryEvent(double timestamp, int factoryId)
	: Event{ timestamp }, factoryId(factoryId){};

void DestoryFactoryEvent::run() {
	cout << "Destory factory with id: " << factoryId << " in timestamp of " << this->getTimestamp() << endl;
}