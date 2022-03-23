#include "researchEvent.h"


ResearchEvent::ResearchEvent(double timestamp, string technology) 
	: Event{ timestamp }, technology(technology) { };

void ResearchEvent::run() {
	cout << "Hello from research Event with technology: "
		<< technology << " and timestamp: " << this->getTimestamp() << endl;

	vector<string> event={"5",to_string(this->getTimestamp()),technology};
	JsonParser::testFunction(event);
}