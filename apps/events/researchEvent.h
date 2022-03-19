#pragma once


#include "event.h"
#include <string>
#include <iostream>

using namespace std;

class ResearchEvent : public Event {
private:
	string technology;
public:
	ResearchEvent(double timestamp, string technology);
	void run() override;
};