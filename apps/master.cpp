#include "master.h"


Master::Master()
{
	std::vector<Event> events;
	
	state = State::getInstance();
	
	/*for (Recipe r : state->getPossibleRecipes()) {
		shared_ptr<Factory> factory  = this->getFactoryForRecipe(r.getCategory());
		start
	}*/

	for (int i = 0; i < 3; ++i) {
		state->incrementTick();
		Recipe r = state->getPossibleRecipes()[0];
		std::shared_ptr<Factory> factory = this->getFactoryForRecipe(r.getCategory());
		startFactoryEvent(factory, r);
	}
	
	/*Recipe r = state->getPossibleRecipes()[0];
	std::shared_ptr<Factory> factory = this->getFactoryForRecipe(r.getCategory());
	startFactoryEvent(factory, r);*/
}

Master::~Master()
{
	state->destory();
}

std::shared_ptr<Factory> Master::getFactoryForRecipe(std::string category)
{
	
	for (std::shared_ptr<Factory> f : state->getNotStartedFactories()) {
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

		auto it = find_if(state->getNotStartedFactories().begin(),
			state->getNotStartedFactories().end(),
			[factory](std::shared_ptr<Factory> obj) {return obj->getName() == factory->getName(); });
		auto index = std::distance(state->getNotStartedFactories().begin(), it);
		std::shared_ptr<Factory> f = state->getNotStartedFactories()[index];

		std::shared_ptr<StartFactoryEvent> e = std::shared_ptr<StartFactoryEvent>(new StartFactoryEvent(
			state->getCurrentTick(), f->getFactoryId(), recipe.getName()
		));

		e->run();
		state->getNotStartedFactories().erase(state->getNotStartedFactories().begin() + index);
	}

}




