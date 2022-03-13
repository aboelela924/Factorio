#include "master.h"


Master::Master()
{
	std::vector<Event> events;
	
	state = State::getInstance();
	


	for (int i = 0; i < 100000; ++i) {
		

	

		std::vector<Recipe> recipes = this->getNewRecipes(state->getPossibleRecipes());
		for (Recipe r : recipes) {
			this->getFactoryEventForNewRecipe(r);
		}
		
		
		
		state->incrementTick();
		
		this->sortFactoryEvents(this->buildFactoryEvents);
		for (std::shared_ptr<BuildFactoryEvent> f : this->buildFactoryEvents) {
			f->run();
		}
		this->buildFactoryEvents.clear();

		if (i == 0) {
			this->possibleCombinationOfEventsToRun();
			this->sortFactoryEvents(this->activeFactoryEvents);
		}
		
		for (std::shared_ptr<FactoryEvent> f : this->activeFactoryEvents) {
			if (f == nullptr) continue;
			f->run();
		}
		
		

		if (i % 10 == 0) {
			std::cout << "Current Time Tick: " << state->getCurrentTick() << std::endl;
			for (std::shared_ptr<Item> i : state->getItemsState()) {
				std::cout << "Item Name: " << i->getName() << ", Amount: " << i->getAmount() << std::endl;
			}
			std::cout << "\n*------------------------------------*\n";
		}
	}
}

Master::~Master()
{
	state->destory();
}






std::vector<Recipe> Master::getNewRecipes(const std::vector<Recipe>& recipes)
{
	std::vector<Recipe> allowableRecipes;
	for (Recipe r : recipes) {
		if (!this->usedRecipes.contains(r)) {
			this->usedRecipes.insert(r);
			allowableRecipes.push_back(r);
		}
	}
	return allowableRecipes;
}

void Master::getFactoryEventForNewRecipe(Recipe& r)
{
	
	if (!state->getBuiltFactories().empty()) {
		for (std::shared_ptr<Factory> f : state->getBuiltFactories()) {
			for (std::string c : f->getCraftingCategories()) {
				if (c == r.categorie) {
					std::shared_ptr<StartFactoryEvent> fe = std::shared_ptr<StartFactoryEvent>(new StartFactoryEvent(
						this, state->getNextTick(), f->getFactoryId(), r.name
					));
					this->starvedFactoryEvents.push_back(fe);
					return;
				}
			}
		}
	}
	
	bool factoryFound = false;
	for (Factory f : state->getFactoryPool()) {
		if (f.getName() == "player") {
			continue;
		}
		for (std::string factoryCategory : f.getCraftingCategories()) {
			if (factoryCategory == r.getCategory()) {
				int factoryId = state->getNewFactoryId();
				std::shared_ptr<BuildFactoryEvent>  buildFactory =
					std::shared_ptr<BuildFactoryEvent>(new BuildFactoryEvent(
						state->getNextTick(), factoryId, f.getFactoryType(), f.getName()
					));

				this->buildFactoryEvents.push_back(buildFactory);

				std::shared_ptr<StartFactoryEvent> startFactory =
					std::shared_ptr<StartFactoryEvent>(new StartFactoryEvent(
						this, state->getNextTick(), factoryId, r.getName()
					));

				this->starvedFactoryEvents.push_back(startFactory);
				factoryFound = true;
			}
		}
		if (factoryFound) {
			break;
		}
	}
	
	
}

void Master::eventDone(FactoryEvent* e)
{
	std::vector<Recipe> recipes = this->getNewRecipes(state->getPossibleRecipes());
	for (Recipe r : recipes) {
		this->getFactoryEventForNewRecipe(r);
	}

	StartFactoryEvent* startFactoryEvent = dynamic_cast<StartFactoryEvent*>(e);

	int startFactoryEventIndex = -1;

	for (int i = 0; i != this->activeFactoryEvents.size(); ++i) {
		std::shared_ptr<StartFactoryEvent> oldEvent = this->activeFactoryEvents[i];
		if (oldEvent.get() == startFactoryEvent) {
			startFactoryEventIndex = i; 
		}
	}

	if (startFactoryEventIndex != -1) {
		std::vector<std::shared_ptr<StartFactoryEvent>>::iterator it =
			this->activeFactoryEvents.begin() + startFactoryEventIndex;
		std::shared_ptr<StartFactoryEvent> oldEvent = this->activeFactoryEvents[startFactoryEventIndex];
		this->activeFactoryEvents.erase(it);
		this->starvedFactoryEvents.push_back(oldEvent);
	}


	this->possibleCombinationOfEventsToRun();
}


void Master::possibleCombinationOfEventsToRun()
{
	std::map<std::string, int> ingredients;
	
	int lastIndex = -1;

	this->sortFactoryEvents(this->starvedFactoryEvents);

	for (int i = 0; i < this->starvedFactoryEvents.size(); ++i) {
		std::string recipeName = this->starvedFactoryEvents[i]->getRecipeName();
		for (Item item : this->state->getRecipeByName(recipeName).getIngredients()) {
			if (ingredients.find(item.getName()) == ingredients.end()) {
				ingredients[item.getName()] = item.getAmount();
			}
			else {
				ingredients[item.getName()] += item.getAmount();
			}
		}
		lastIndex = i ;
		if (!haveEnoughResources(ingredients)) {
			lastIndex = i - 1;
			break;
		}
	}
	if (lastIndex != -1) {
		auto it = this->starvedFactoryEvents.begin() + lastIndex + 1;

		for (auto newIt = this->starvedFactoryEvents.begin(); newIt != it; ++newIt) {
			(*newIt)->setStartingTimeStamp(state->getNextTick());
		}
		this->activeFactoryEvents.insert(this->activeFactoryEvents.end(),
			this->starvedFactoryEvents.begin(), it);

		this->starvedFactoryEvents.erase(this->starvedFactoryEvents.begin(), it);
	}
	if(areAllIngredientsEmpty()) {
		for (auto newIt = this->starvedFactoryEvents.begin(); 
			newIt != this->starvedFactoryEvents.end(); ++newIt) {
			(*newIt)->setStartingTimeStamp(state->getNextTick());
		}
		this->activeFactoryEvents.insert(this->activeFactoryEvents.end(),
			this->starvedFactoryEvents.begin(), this->starvedFactoryEvents.end());
		this->starvedFactoryEvents.clear();
	}
	
}

bool Master::haveEnoughResources(std::map<std::string, int> ingredientsSum)
{
	for (auto it = ingredientsSum.begin(); it != ingredientsSum.end(); ++it) {
		std::string name = it->first;
		int amount = it->second;

		std::shared_ptr<Item> i = state->getItemByName(name);

		if (amount > i->getAmount()) {
			return false;
		}
	}
	return true;
}

bool Master::areAllIngredientsEmpty()
{
	for (std::shared_ptr<StartFactoryEvent> factoryEvent : this->starvedFactoryEvents) {
		std::string recipeName = factoryEvent->getRecipeName();
		if (this->state->getRecipeByName(recipeName).getIngredients().size() != 0) {
			return false;
		}
	}
	return true;
}








