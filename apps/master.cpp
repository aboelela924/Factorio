#include "master.h"
#include "model/challenge.h"
#include "jsonParser.cpp"

Master::Master(std::string mainPath)
{
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

	this->getPossibleRecipes();

}

std::vector<Recipe> Master::getPossibleRecipes()
{
	
	std::vector<Recipe> possibleRecipes;

	for (Recipe r : this->recipesPool) {
		if (checkIfRequirementIsFullfilled(r.getIngredients())) {
			r.setEnabled(true);
		}
	}

	return possibleRecipes;
}

bool Master::checkIfRequirementIsFullfilled(std::vector<Item> requirements)
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
