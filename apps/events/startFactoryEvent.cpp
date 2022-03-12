#include "startFactoryEvent.h"

StartFactoryEvent::StartFactoryEvent(Feedback* feedback, double timestamp, int factoryId, string recipe)
	: FactoryEvent{ timestamp, factoryId }, recipe(recipe) , feedback(feedback)
{
	this->feedback->runningProjectIds.insert(factoryId);
};

void StartFactoryEvent::run() {
	

	State* state = State::getInstance();
	Recipe r = state->getRecipeByName(this->recipe);
	std::shared_ptr<Factory> f = state->getFactoryById(factoryId);

	if (this->isFactoryStillRunning(state->getCurrentTick(), r.getEnergy(), f->getCraftingSpeed())) {
		//std::cout << "Current Tick: " << state->getCurrentTick() << " ,Working on factory " << f->getFactoryId() << " on recicpe " << r.getName() << std::endl;
	}
	else if (this->isDone(state->getCurrentTick(), r.getEnergy(), f->getCraftingSpeed())) {
		this->feedback->runningProjectIds.erase(factoryId);
		
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
		}

		this->feedback->eventDone(this);
		this->timestamp = state->getCurrentTick();
	}
	else {
		std::cout << "Current Tick: " << state->getCurrentTick() << " ,Start factory with Id: " << f->getFactoryId() << " on recicpe " << r.getName() << std::endl;


		for (Item i : r.getIngredients()) {
			std::shared_ptr<Item> item_ptr = state->getItemByName(i.getName());
			item_ptr->decreaseAmountBy(i.getAmount());
		}

		feedback->factoryTimeMapping[factoryId].push_back(r.getEnergy());
		for (Item i : r.getIngredients()) {
			state->getItemByName(i.getName())->decreaseAmountBy(i.getAmount());
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
