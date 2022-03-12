#include "master.h"


Master::Master()
{
	std::vector<Event> events;
	
	state = State::getInstance();
	


	for (int i = 0; i < 10000; ++i) {
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

		

		for (std::shared_ptr<FactoryEvent> f : this->activeFactoryEvents) {
			f->run();
		}
		
		this->combineStarvedAndActiveEvents();
		this->sortFactoryEvents(this->activeFactoryEvents);
		this->possibleCombinationOfEventsToRun();

		if (i % 60 == 0) {
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
			if (this->runningProjectIds.find(f->getFactoryId()) == this->runningProjectIds.end()) {
				for (std::string c : f->getCraftingCategories()) {
					if (c == r.categorie) {
						std::shared_ptr<StartFactoryEvent> fe = std::shared_ptr<StartFactoryEvent>(new StartFactoryEvent(
							std::move(this), state->getNextTick(), f->getFactoryId(), r.name
						));
						this->activeFactoryEvents.push_back(fe);
						return;
					}
				}
			}
			
		}
	}
	
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

				this->activeFactoryEvents.push_back(startFactory);
			}
		}
	}
	
	
}

void Master::eventDone(FactoryEvent* event)
{

	std::cout << "Factory with id: " << event->getFactoryId() << " has finished executing" << std::endl;
}


void Master::possibleCombinationOfEventsToRun()
{
	std::map<std::string, int> ingredients;
	
	int lastIndex = -1;

	for (int i = 0; i < this->activeFactoryEvents.size(); ++i) {
		std::string recipeName = this->activeFactoryEvents[i]->getRecipeName();
		for (Item item : this->state->getRecipeByName(recipeName).getIngredients()) {
			if (ingredients.find(item.getName()) == ingredients.end()) {
				ingredients[item.getName()] = item.getAmount();
			}
			else {
				ingredients[item.getName()] += item.getAmount();
			}
		}

		if (!haveEnoughResources(ingredients)) {
			lastIndex = i;
			break;
		}
	}
	if (lastIndex != -1) {
		auto it = this->activeFactoryEvents.begin() + lastIndex ;
		this->starvedFactoryEvents.insert(this->starvedFactoryEvents.end(),
			it, this->activeFactoryEvents.end());

		this->activeFactoryEvents.erase(it, this->activeFactoryEvents.end());
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

void Master::combineStarvedAndActiveEvents()
{
	this->activeFactoryEvents.insert(
		this->activeFactoryEvents.end(), this->starvedFactoryEvents.begin(),
		this->starvedFactoryEvents.end()
	);

	this->starvedFactoryEvents.clear();

}






