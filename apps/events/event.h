#pragma once
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iomanip>
#include "../jsonParser.h"

class Event {

protected:
	double timestamp;

public:
	Event(double timestamp) ;
	virtual void run() = 0;
	// virtual void to_json(json& myJson) = 0;

	double getTimestamp();
	/*{
		return this->timestamp;
	}*/
};


