#include  "destoryFactoryEvent.h"
#include <nlohmann/json.hpp>
#include <iomanip>

DestoryFactoryEvent::DestoryFactoryEvent(double timestamp, int factoryId)
	: Event{ timestamp }, factoryId(factoryId){};

void DestoryFactoryEvent::run() {
	cout << "Destory factory with id: " << factoryId << " in timestamp of " << this->getTimestamp() << endl;
	// vector<string> event={"3",to_string(this->getTimestamp()),to_string(factoryId)};
	// JsonParser::testFunction(event);

	vector<string> event={"3",to_string(this->getTimestamp()),to_string(factoryId)};
	JsonParser::testFunction(event);
}