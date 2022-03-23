#pragma once

#include "factoryEvent.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <iomanip>

using namespace std;


class StopFactoryEvent : public FactoryEvent {
private:
	

public:

	StopFactoryEvent(double timestamp, int factoryId);	
	void run() override;
	// void to_json(json& myJson) override;

};