#include "victoryEvent.h"

VictoryEvent::VictoryEvent(double timestamp) : Event{ timestamp } {};

void VictoryEvent::run() {
	vector<string> event={"6",to_string(this->getTimestamp())};
	JsonParser::testFunction(event);
}