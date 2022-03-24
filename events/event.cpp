#include "event.h"

Event::Event(double timestamp) : timestamp(timestamp) {};

double Event ::getTimestamp() {
	return this->timestamp;
}
