#include "victoryEvent.h"

VictoryEvent::VictoryEvent(double timestamp) : Event{ timestamp } {};

void VictoryEvent::run() {
	cout << "Vicotry Event with timestamp: " << this->getTimestamp() << endl;
}