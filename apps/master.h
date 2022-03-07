#pragma once
#include <string>
#include <memory>
#include "state.h"

#include "events/event.h"
#include "events/researchEvent.h"
#include "events/buildFactoryEvent.h"
#include "events/destoryFactoryEvent.h"
#include "events/startFactoryEvent.h"
#include "events/stopFactoryEvent.h"
#include "events/victoryEvent.h"

#include "model/factory.h"

class Master {
public:
	Master();
	~Master();
	
	std::shared_ptr<Factory> getFactoryForRecipe(std::string category);
	void startFactoryEvent(std::shared_ptr<Factory> factory, Recipe recipe);
	

private:
	State* state;
	std::shared_ptr<Event> factoryEvents;
};
