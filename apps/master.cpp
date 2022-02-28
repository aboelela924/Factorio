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

	std::cout << "Tech name is : " << technologiesPool.size();
}
