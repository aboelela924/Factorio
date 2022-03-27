#include "master.h"
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <cmath>


Master::Master(std::string challengeName)
{
	std::vector<Event> events;
	state = State::getInstance(challengeName);
	while(!state->isGoalItemAchieved() || state->getCurrentTick()>=pow(2,40)){
		// for (int i = 0; i < 100; ++i) { //100000
		// if(!state->isGoalItemAchieved()) break;
		// bool a=state->isGoalItemAchieved();
		// if(a) break;

		std::vector<Recipe> recipes = this->getNewRecipes(state->getPossibleRecipes());		
 		for (Recipe r : recipes) {
			this->getFactoryEventForNewRecipe(r);
		}

		
		std::vector<Technology> technologies = this->getNewTechnologies(state->getPossibleTechnology());
		for (Technology t : technologies) {
			this->createResearchEventForTechnology(t);
		}


		this->possibleCombinationOfEventsToRun();
		this->sortFactoryEvents(this->activeFactoryEvents); 
		state->incrementTick();

		
		for (std::shared_ptr<ResearchEvent> t_ptr : this->activeResearchEvents) {
			t_ptr->run();
		}

		this->activeResearchEvents.clear();

		this->sortFactoryEvents(this->buildFactoryEvents);
		json j;
		for (std::shared_ptr<BuildFactoryEvent> f : this->buildFactoryEvents) {
			f->run();
			// f->to_json(j);

		}
		this->buildFactoryEvents.clear();
		
		for (std::shared_ptr<FactoryEvent> f : this->activeFactoryEvents) {
			if (f == nullptr) continue;
			f->run();
		}
		
	}
	vector<string> event={"7"};
	JsonParser::testFunction(event);
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

std::vector<Technology> Master::getNewTechnologies(std::vector<Technology> technologies)
{

	std::vector<Technology> allowableTechnologies;

	for (Technology t : technologies) {
		if (!this->usedTechnologies.contains(t.getName())) {
			this->usedTechnologies.insert(t.getName());
			allowableTechnologies.push_back(t);
		}
	}

	return allowableTechnologies;
}


void Master::createResearchEventForTechnology(Technology& t)
{

	std::shared_ptr<ResearchEvent> e =
		std::shared_ptr<ResearchEvent>(
			new ResearchEvent(state->getNextTick(), t.getName())
			);
	this->starvedResearchEvents.push_back(e);
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
					state->moveFactory(f->getFactoryId(),
						state->getBuiltFactories(), state->getStarvedFactories());
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
				f.setFactoryId(factoryId);
				std::shared_ptr<Factory> factory = std::shared_ptr<Factory>(new Factory(f));

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
				state->addStarvedFactory(factory);
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
		state->moveFactory(oldEvent->getFactoryId(),
			state->getRunningFactories(), state->getStarvedFactories());
		this->activeFactoryEvents.erase(it);
		this->starvedFactoryEvents.push_back(oldEvent);
	}

	this->checkForFactoryToStop(e);
	
}


void Master::possibleCombinationOfEventsToRun()
{
	std::map<std::string, int> ingredients;
	
	int lastIndex = -1;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	shuffle(this->starvedFactoryEvents.begin(), this->starvedFactoryEvents.end(), std::default_random_engine(seed));

	seed = std::chrono::system_clock::now().time_since_epoch().count();

	shuffle(this->starvedResearchEvents.begin(), this->starvedResearchEvents.end(), std::default_random_engine(seed));
	

	for (int i = 0; i < this->starvedResearchEvents.size(); ++i) {
		std::string technologyName = this->starvedResearchEvents[i]->getTechnologyName();
		Technology t = state->getTechnologyByName(technologyName);
		for (Item item : t.getIngredients()) {
			if (ingredients.find(item.getName()) == ingredients.end()) {
				ingredients[item.getName()] = item.getAmount();
			}
			else {
				ingredients[item.getName()] += item.getAmount();
			}
		}
		lastIndex = i;
		if (!haveEnoughResources(ingredients)) {
			lastIndex = i - 1;
			break;
		}
	}

	if (lastIndex != -1) {
		auto it = this->starvedResearchEvents.begin() + lastIndex + 1;

		this->activeResearchEvents.insert(this->activeResearchEvents.end(),
			this->starvedResearchEvents.begin(), it);

		this->starvedResearchEvents.erase(this->starvedResearchEvents.begin(), it);

		std::sort(this->activeResearchEvents.begin(),
			this->activeResearchEvents.end(),
			[](std::shared_ptr<ResearchEvent>& lhs, std::shared_ptr<ResearchEvent>& rhs)
			{
				return lhs->getTechnologyName() < rhs->getTechnologyName();
			});
	}


	

	if (lastIndex > -1 && lastIndex < this->starvedResearchEvents.size() -1) {
		return;
	}

	lastIndex = -1;

	for (int i = 0; i < this->starvedFactoryEvents.size(); ++i) {
		std::string recipeName = this->starvedFactoryEvents[i]->getRecipeName();
		Recipe r = this->state->getRecipeByName(recipeName);
		std::vector<Item> ing = r.getIngredients();
		for (Item item : ing) {
			if (ingredients.find(item.getName()) == ingredients.end()) {
				ingredients[item.getName()] = item.getAmount();
			}
			else {
				ingredients[item.getName()] += item.getAmount();
			}
		}
		lastIndex = i;
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
		
		int index = std::distance(this->starvedFactoryEvents.begin(), it);
		for (int i = 0; i < index; ++i) {
			state->moveFactory(this->starvedFactoryEvents[i]->getFactoryId(),
				state->getStarvedFactories(), 
				state->getRunningFactories()
			);
		}
		
		this->activeFactoryEvents.insert(this->activeFactoryEvents.end(),
			this->starvedFactoryEvents.begin(), it);

		this->starvedFactoryEvents.erase(this->starvedFactoryEvents.begin(), it);
		
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

void Master::checkForFactoryToStop(FactoryEvent* e)
{

	StartFactoryEvent* startFactoryEvent = dynamic_cast<StartFactoryEvent*>(e);
	std::string recipeName = startFactoryEvent->getRecipeName();

	Recipe r = state->getRecipeByName(recipeName);
	
	bool isDone = true;

	for (Item i : r.getProducts()) {
		if (state->getItemAccumlatedAmount(i.getName())  < state->getItemAmount(i.getName())) {
			isDone = false;
		}
	}

	if (isDone) {

		auto it = find_if(this->starvedFactoryEvents.begin(),
			this->starvedFactoryEvents.end(),
			[&startFactoryEvent](std::shared_ptr<StartFactoryEvent> e) { return e.get() == startFactoryEvent; });

		if (it != this->starvedFactoryEvents.end()) {
			this->starvedFactoryEvents.erase(it);
		}

		StopFactoryEvent stopFactory = StopFactoryEvent(state->getCurrentTick(), e->getFactoryId());
		stopFactory.run();
		DestoryFactoryEvent destoryFactory = DestoryFactoryEvent(state->getCurrentTick(), e->getFactoryId());
		destoryFactory.run();

	}

}










