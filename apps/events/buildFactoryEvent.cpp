#include "buildFactoryEvent.h"
// #include "../jsonWriter.h"





BuildFactoryEvent::BuildFactoryEvent(double timestamp, int factoryId, string factoryType, string factoryName)
	: FactoryEvent{ timestamp, factoryId }, factoryType(factoryType), factoryName(factoryName) {};

void BuildFactoryEvent::run() {
	cout << endl << "call Build event " << endl;
	cout << "Build Factory id: " << factoryId << ", Factory type: " << factoryType
		<< "Factory name: " << factoryName << " and timestamp: " << this->getTimestamp() << endl;
		
	vector<string> event={"1",to_string(this->getTimestamp()),to_string(factoryId),factoryType,factoryName};
	JsonParser::testFunction(event);
	

	// vector<string> event2={"4"};
	// JsonParser::testFunction(event2);


	State* state = State::getInstance();
	/*Factory f = state->getFactoryByName(factoryName);
	f.setFactoryId(this->factoryId);
	f.setFactoryType(this->factoryType);
	state->addBuiltFactories(f);*/


	
}

// void BuildFactoryEvent::to_json(json& myJson)
// {
// 	myJson.push_back({{"test","test"}});
// }