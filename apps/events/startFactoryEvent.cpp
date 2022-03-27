#include "startFactoryEvent.h"
// #include "../jsonWriter.h"


StartFactoryEvent::StartFactoryEvent(Feedback* feedback, double timestamp, int factoryId, string recipe)
	: FactoryEvent{ timestamp, factoryId }, recipe(recipe) , feedback(feedback)
{
	State* state = State::getInstance();
};

void StartFactoryEvent::run() {


	const void * address = static_cast<const void*>(this);
	std::stringstream ss;
	ss << address;  
	std::string name = ss.str();

	if (this->feedback->eventsSet.find(name)==this->feedback->eventsSet.end()) {
		this->feedback->eventsSet.insert(name);
		vector<string> event={"2",to_string(this->getTimestamp()),to_string(factoryId),recipe};
		JsonParser::testFunction(event);
	 }


	State* state = State::getInstance();
	Recipe r = state->getRecipeByName(this->recipe);
	std::shared_ptr<Factory> f = state->getFactoryById(factoryId);

	if (this->isFactoryStillRunning(state->getCurrentTick(), r.getEnergy(), f->getCraftingSpeed())) {
		//std::cout << "Current Tick: " << state->getCurrentTick() << " ,Working on factory " << f->getFactoryId() << " on recicpe " << r.getName() << std::endl;
	}
	else if (this->isDone(state->getCurrentTick(), r.getEnergy(), f->getCraftingSpeed())) {
		
		for (Item i : r.getProducts()) {
			std::shared_ptr<Item> item_ptr = state->getItemByName(i.getName());
			if (item_ptr != nullptr) {
				item_ptr->increaseAmoutnBy(i.getAmount());
			}
			else {
				std::shared_ptr<Item> item_ptr = state->getItemByNameFromItemPool(i.getName());
				item_ptr->increaseAmoutnBy(i.getAmount());
				state->getItemsState().push_back(item_ptr);
			}
			state->addItemToAccumlationMap(i.getName(), i.getAmount());
		}

		this->feedback->eventDone(this);
	}
	else {
		



		for (Item i : r.getIngredients()) {
			std::shared_ptr<Item> item_ptr = state->getItemByName(i.getName());
			item_ptr->decreaseAmountBy(i.getAmount());
		}

	}

}

std::string StartFactoryEvent::getRecipeName()
{
	return this->recipe;
}

bool StartFactoryEvent::isFactoryStillRunning(double currentTick, int energy, double craftingSpeed)
{	
	double timeRequired = energy / craftingSpeed;

	if (currentTick > this->timestamp
		&& currentTick < this->timestamp + timeRequired) {
		return true;
	}
	return false;
}

bool StartFactoryEvent::isDone(double currentTick, int energy, double craftingSpeed)
{
	double timeRequired = energy / craftingSpeed;


	if (currentTick >= this->timestamp + timeRequired) {
		return true;
	}
	return false;
}

void StartFactoryEvent::setStartingTimeStamp(double tick)
{
	this->timestamp = tick;
}


// void StartFactoryEvent::to_json(json& myJson)
// {
// 	myJson.push_back({{"test","test"}});
// }