#include "state.h"
#include "utils.h"

State* State::instance = 0;

State::State() {
	std::string mainPath = Utils::getexepath();
	std::string delimiter = "out";
	mainPath = mainPath.substr(0, mainPath.find(delimiter));

	std::string challengePath = mainPath + "/data/factorio-simulator/inputs/challenge-2.json";
	Challenge challenge = JsonParser::readChallenge(challengePath);

	std::string recipesPath = mainPath + "/data/factorio-data/recipe.json";
	this->recipesPool = JsonParser::readRecipe(recipesPath);

	std::string itemsPath = mainPath + "/data/factorio-data/item.json";
	this->itemsPool = JsonParser::readItems(itemsPath);

	std::string factoriesPath = mainPath + "/data/factorio-data/factory.json";
	this->factoriesPool = JsonParser::readFactories(factoriesPath);

	std::string technologiesPath = mainPath + "/data/factorio-data/technology.json";
	this->technologiesPool = JsonParser::readTechnology(technologiesPath);

	for (Item item : challenge.getInitialItems()) {
		this->itemsState.push_back(std::shared_ptr<Item>(new Item(item)));
	}

	for (Factory f : challenge.getFactories()) {
		std::string name = f.getName();

		auto it = find_if(this->factoriesPool.begin(),
			this->factoriesPool.end(),
			[&name](Factory& obj) {return obj.getName() == name; });

		auto index = std::distance(this->factoriesPool.begin(), it);
		for (std::string category : this->factoriesPool[index].getCraftingCategories()) {
			f.getCraftingCategories().push_back(category);
		}
		f.setCraftingSpeed(this->factoriesPool[index].getCraftingSpeed());

		this->notStartedFactoriesState.push_back(std::shared_ptr<Factory>(new Factory(f)));
	}

	for (int i = 0; i < 10000; ++i) {
		idPool.push_back(i);
	}
}


State* State::getInstance() {
	if (!instance) {
		instance = new State();
	}
	return instance;
}


double State::getCurrentTick()
{
	return this->currentTick;
}
void State::incrementTick()
{
	if (this->currentTick == -1) {
		this->currentTick = 0;
	}
	else {
		this->currentTick += 60;
	}
}



bool State::checkIfRequirementIsFullfilled(std::vector<Item> requirements)
{
	for (Item i : requirements) {
		std::string name = i.getName();
		auto it = find_if(this->itemsState.begin(),
			this->itemsState.end(),
			[&name](std::shared_ptr<Item> obj) {return obj->getName() == name; });

		if (it != this->itemsState.end())
		{
			auto index = std::distance(this->itemsState.begin(), it);
			if (this->itemsState[index]->getAmount() < i.getAmount()) {
				return false;
			}
		}
		else {
			return false;
		}
	}


	return true;
}
bool State::checkIfTechnologyPrerequisitesIfFullfilled(vector<std::string> prerequisites)
{
	for (std::string p : prerequisites) {
		auto it = find_if(this->technologiesPool.begin(),
			this->technologiesPool.end(),
			[&p](Technology& obj) {return obj.getName() == p; });

		if (it != this->technologiesPool.end())
		{
			auto index = std::distance(this->technologiesPool.begin(), it);
			if (!this->technologiesPool[index].getEnabled()) {
				return false;
			}
		}
		else {
			return false;
		}
	}

	return true;
}


Recipe State::getRecipeByName(std::string name)
{

	auto it = find_if(this->recipesPool.begin(),
		this->recipesPool.end(),
		[&name](Recipe& obj) {return obj.getName() == name; });

	auto index = std::distance(this->recipesPool.begin(), it);
	return this->recipesPool[index];

	/*if (it != this->recipesPool.end())
	{
		auto index = std::distance(this->recipesPool.begin(), it);
		return this->recipesPool[index];
	}

	return null;*/
}
std::shared_ptr<Item> State::getItemByName(std::string name)
{
	auto it = find_if(this->itemsState.begin(),
		this->itemsState.end(),
		[&name](std::shared_ptr<Item> obj) {return obj->getName() == name; });

	

	if (it != this->itemsState.end()) {
		auto index = std::distance(this->itemsState.begin(), it);
		return this->itemsState[index];
	}

	return nullptr;
}
std::shared_ptr<Item> State::getItemByNameFromItemPool(std::string name) {
	auto it = find_if(this->itemsPool.begin(),
		this->itemsPool.end(),
		[&name](Item& obj) {return obj.getName() == name; });
	auto index = std::distance(this->itemsPool.begin(), it);
	return std::shared_ptr<Item>(new Item(this->itemsPool[index]));
}

std::vector<Recipe> State::getPossibleRecipes()
{
	std::vector<Recipe> possibleRecipes;

	for (Recipe r : this->recipesPool) {
		if (r.getEnbaled() && checkIfRequirementIsFullfilled(r.getIngredients())) {
			possibleRecipes.push_back(r);
		}
	}

	return possibleRecipes;
}
std::vector<Technology> State::getPossibleTechnology()
{
	std::vector<Technology> possibleTechnologies;

	for (Technology t : this->technologiesPool) {
		if (checkIfRequirementIsFullfilled(t.getIngredients())
			&& checkIfTechnologyPrerequisitesIfFullfilled(t.getPrerequisites())) {
			possibleTechnologies.push_back(t);
		}
	}


	return possibleTechnologies;
}


std::vector<std::shared_ptr<Item>>& State::getItemsState()
{
	return this->itemsState;
}
std::vector<std::shared_ptr<Technology>>& State::getTechonogiesState()
{
	return this->techonogiesState;
}


void State::addBuiltFactories(Factory newFactory)
{
	this->notStartedFactoriesState.push_back(std::shared_ptr<Factory>(new Factory(newFactory)));
}
std::vector<Factory> State::getFactoryPool()
{
	return this->factoriesPool;
}
std::vector<std::shared_ptr<Factory>>& State::getActiveFactoriesState()
{
	return this->activeFactoriesState;
}
std::vector<std::shared_ptr<Factory>>& State::getStarvedFactoriesState()
{
	return this->starvedFactoriesState;
}
std::shared_ptr<Factory> State::getFactoryById(int id)
{
	
	std::vector<shared_ptr<Factory>> allFactories = std::vector<shared_ptr<Factory>>();
	
	allFactories.insert(allFactories.end(), this->notStartedFactoriesState.begin(),
		this->notStartedFactoriesState.end());
	
	allFactories.insert(allFactories.end(), this->activeFactoriesState.begin(),
		this->activeFactoriesState.end());

	allFactories.insert(allFactories.end(), this->starvedFactoriesState.begin(), 
		this->starvedFactoriesState.end());
	
	auto it = find_if(allFactories.begin(),
		allFactories.end(),
		[&id](std::shared_ptr<Factory> obj) {return obj->getFactoryId() == id; });
	if (it != allFactories.end()) {
		auto index = std::distance(allFactories.begin(), it);
		return allFactories[index];
	}



	return nullptr;
}
std::vector<std::shared_ptr<Factory>>& State::getNotStartedFactories()
{
	return this->notStartedFactoriesState;
}
int State::getNewFactoryId() {
	std::sort(this->idPool.begin(), this->idPool.end());
	int id = this->idPool[0];
	this->idPool.erase(this->idPool.begin());
	return id;
}




void State::destory() {
	delete instance;
	instance = NULL;
}