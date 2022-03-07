#include "startFactoryEvent.h"

StartFactoryEvent::StartFactoryEvent(double timestamp, int factoryId, string recipe)
	: Event{ timestamp }, factoryId(factoryId), recipe(recipe) 
{

};

void StartFactoryEvent::run() {
	cout << "Start factory with id: " << factoryId <<
		", recipe: " << recipe << ", Timestamp: " << timestamp << endl;

	State* state = State::getInstance();

	Recipe r = state->getRecipeByName(this->recipe);

	std::shared_ptr<Factory> f = state->getFactoryById(factoryId);

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

bool StartFactoryEvent::isFactoryStillRunning()
{
	return false;
}
