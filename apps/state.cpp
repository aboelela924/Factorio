#include "state.h"
#include "utils.h"

State* State::instance = 0;

State::State() {
	std::string mainPath = Utils::getexepath();
	std::string delimiter = "out";
	mainPath = mainPath.substr(0, mainPath.find(delimiter));

	std::string challengePath = mainPath + "/data/factorio-data/example-challenge.json";
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
		this->itemsState.push_back(item);
	}
}


State* State::getInstance() {
	if (!instance) {
		instance = new State();
	}
	return instance;
}


bool State::checkIfRequirementIsFullfilled(std::vector<Item> requirements)
{
	for (Item i : requirements) {
		std::string name = i.getName();
		auto it = find_if(this->itemsState.begin(),
			this->itemsState.end(),
			[&name](Item& obj) {return obj.getName() == name; });

		if (it != this->itemsState.end())
		{
			auto index = std::distance(this->itemsState.begin(), it);
			if (this->itemsState[index].getAmount() < i.getAmount()) {
				return false;
			}
		}
		else {
			return false;
		}
	}


	return true;
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
		//if(checkIfRequirementIsFullfilled())
	}


	return std::vector<Technology>();
}

std::vector<Item> State::getItemsState()
{
	return this->itemsState;
}

std::vector<Technology> State::getTechonogiesState()
{
	return this->techonogiesState;
}

std::vector<Factory> State::getActiveFactoriesState()
{
	return this->activeFactoriesState;
}

std::vector<Factory> State::getStarvedFactoriesState()
{
	return this->starvedFactoriesState;
}


void State::destory() {
	delete instance;
	instance = NULL;
}