#include "master.h"


Master::Master()
{
	std::vector<Event> events;
	
	state = State::getInstance();
	


	for (int i = 0; i < 5; ++i) {
		std::vector<Recipe> recipes = this->getNewRecipes(state->getPossibleRecipes());
		for (Recipe r : recipes) {
			this->getFactoryEventForNewRecipe(r);
			state->incrementTick();
			for (std::shared_ptr<FactoryEvent> f : this->activeFactoryEvents) {
				f->run();
			}
		}
		
	}
}

Master::~Master()
{
	state->destory();
}



std::shared_ptr<Factory> Master::getFactoryForRecipe(std::string category)
{
	
	for (std::shared_ptr<Factory> f : state->getCombinedFactories()) {
		for (std::string factoryCategory : f->getCraftingCategories()) {
			if (category == factoryCategory) {
				return f;
			}
		}
	}
	
	for (Factory f : state->getFactoryPool()) {
		for (std::string factoryCategory : f.getCraftingCategories()) {
			if (category == factoryCategory) {
				return std::shared_ptr<Factory>(new Factory(f));
			}
		}
	}

	return std::shared_ptr<Factory>();
}

void Master::startFactoryEvent(std::shared_ptr<Factory> factory, Recipe recipe)
{
	if (factory->getFactoryId()  == -1) {
		
		/*factory->setFactoryId(state->getNewFactoryId());

		BuildFactoryEvent buildEvent = BuildFactoryEvent(state->getCurrentTick() + 1,
			factory->getFactoryId(),
			factory->getFactoryType(),
			factory->getName());

		buildEvent.run();*/
	
	}else {

		auto it = find_if(state->getBuiltFactories().begin(),
			state->getBuiltFactories().end(),
			[factory](std::shared_ptr<Factory> obj) {return obj->getName() == factory->getName(); });
		auto index = std::distance(state->getBuiltFactories().begin(), it);
		std::shared_ptr<Factory> f = state->getBuiltFactories()[index];

		std::shared_ptr<StartFactoryEvent> e = std::shared_ptr<StartFactoryEvent>(new StartFactoryEvent(
			state->getCurrentTick(), f->getFactoryId(), recipe.getName()
		));

		e->run();
		state->getBuiltFactories().erase(state->getBuiltFactories().begin() + index);
	}

}

std::vector<Recipe>& Master::getNewRecipes(const std::vector<Recipe>& recipes)
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

void Master::getFactoryEventForNewRecipe(const Recipe& r)
{
	
	if (!state->getBuiltFactories().empty()) {
		for (std::shared_ptr<Factory> f : state->getBuiltFactories()) {
			for (std::string c : f->getCraftingCategories()) {
				if (c == r.categorie) {
					std::shared_ptr<FactoryEvent> fe = std::shared_ptr<FactoryEvent>(new StartFactoryEvent(
						state->getNextTick(), f->getFactoryId(), r.name
					));
					this->activeFactoryEvents.push_back(fe);
					return;
				}
			}
		}
	}
	else {
		std::cout << "There is no build Factory for this " << std::endl;
	}
	
}

void Master::eventDone(FactoryEvent& event)
{

	std::cout << "Factory with id: " << event.getFactoryId() << " has finished executing" << std::endl;
}






