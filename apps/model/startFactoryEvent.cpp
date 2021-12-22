#include "startFactoryEvent.h"

StartFactoryEvent::StartFactoryEvent(double timestamp, int factoryId, string recipe)
	: Event{ timestamp }, factoryId(factoryId), recipe(recipe) {};

void StartFactoryEvent::run() {
	cout << "Start factory with id: " << factoryId <<
		", recipe: " << recipe << ", Timestamp: " << timestamp << endl;
}