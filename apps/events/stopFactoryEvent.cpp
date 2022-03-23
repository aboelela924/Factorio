#include "stopFactoryEvent.h"
#include <nlohmann/json.hpp>
#include <iomanip>


StopFactoryEvent::StopFactoryEvent(double timestamp, int factoryId) 
	: FactoryEvent{ timestamp,  factoryId }{};

void StopFactoryEvent::run() {
	cout << "Start factory event with factory id: " << factoryId << ", timestamp: " << this->getTimestamp() << endl;
	vector<string> event={"4",to_string(this->getTimestamp()),to_string(factoryId)};
	JsonParser::testFunction(event);
	// json j;
    // j.push_back(json{{"type","build-factory-event"},{"timestamp", this->getTimestamp()}, {"factory-id",factoryId},{"factory-type", factoryType},{"factory-name", factoryName} });
    // // std::ofstream o("test_out.json");
    // // o << std::setw(4) << j << std::endl;
	// std::ofstream outfile;
    // outfile.open("test_out.json", std::ios_base::app);
	// outfile << j;
}

// void StopFactoryEvent::to_json(json& myJson)
// {
// 	myJson.push_back({{"test","test"}});
// }