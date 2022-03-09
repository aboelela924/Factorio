#include "startFactoryEvent.h"

StartFactoryEvent::StartFactoryEvent(double timestamp, int factoryId, string recipe)
	: FactoryEvent{ timestamp, factoryId }, recipe(recipe) 
{

};

void StartFactoryEvent::run() {
	

	State* state = State::getInstance();

	Recipe r = state->getRecipeByName(this->recipe);

	std::shared_ptr<Factory> f = state->getFactoryById(factoryId);
	f->increaseRequiredTimeBy(r.getEnergy());
	if (this->timestamp >= state->getCurrentTick() 
		&& this->isFactoryStillRunning(state->getCurrentTick(), f->getFactoryRequiredTime())) {
		

		for (Item i : r.getIngredients()) {
			state->getItemByName(i.getName())->decreaseAmountBy(i.getAmount());
		}

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
	}
	


}

bool StartFactoryEvent::isFactoryStillRunning(double currentTick, double timeRequired)
{	
	if (currentTick > this->timestamp 
		&& currentTick < this->timestamp + timeRequired) {
		return true;
	}
	return false;
}
