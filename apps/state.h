#pragma once
#include <string>
#include <memory>
#include <unordered_set>
#include <map>

#include "model/recipe.h"
#include "model/factory.h"
#include "model/technology.h"
#include "model/item.h"
#include "model/challenge.h"
#include "jsonParser.h"
#include "utils.h"

class State{
private:
	static State* instance;

	State();
	State(const State& cc) {};
	~State() {};

	double currentTick = -1;

	std::vector<Recipe> recipesPool;
	std::vector<Technology> technologiesPool;
	std::vector<Factory> factoriesPool;
	std::vector<Item> itemsPool;

	std::vector<int> idPool;
	
	std::map<std::string, int> accumlatedItemGeneration;
	std::vector<std::shared_ptr<Item>> itemsState;
	std::vector<std::shared_ptr<Technology>> techonogiesState;

	std::vector<std::shared_ptr<Factory>> builtFactories;
	std::vector<std::shared_ptr<Factory>> doneFactories;
	std::vector<std::shared_ptr<Factory>> starvedFactories;
	
	std::vector<std::shared_ptr<Factory>> runningFactories;
	
	std::map<std::string, int> itemAmount;

public:
	
	double getCurrentTick();
	double getNextTick();
	void incrementTick();

	
	void addItemToAccumlationMap(std::string name, int amount);
	int getItemAccumlatedAmount(std::string name);

	void backtrackRecipesForGoalItem(Challenge& c, 
		std::string pathToRecipes, 
		std::string pathToTechnologies);
	void getParent(Item& item, int factor, 
		std::vector<Recipe>& smallRecipePool, 
		std::vector<Technology>& samllTechnologyPool,
		std::unordered_set<std::string>& usedRecipesNames,
		std::unordered_set<std::string>& usedTechnologiesNames);
	Technology& getTechnologyForRecipe(std::string name);
	int getItemAmount(std::string itemName);

	bool checkIfRequirementIsFullfilled(std::vector<Item> requirements);
	bool checkIfTechnologyPrerequisitesIfFullfilled(vector<std::string> prerequisites);

	Recipe getRecipeByName(std::string name);
	std::vector<Recipe> getPossibleRecipes();

	std::shared_ptr<Item> getItemByName(std::string name);
	std::shared_ptr<Item> getItemByNameFromItemPool(std::string name);

	std::vector<Technology> getPossibleTechnology();

	std::vector<std::shared_ptr<Item>>& getItemsState();
	std::vector<std::shared_ptr<Technology>>& getTechonogiesState();

	void addBuiltFactories(Factory newFactory);
	int getNewFactoryId();
	std::vector<Factory> getFactoryPool();
	std::vector<std::shared_ptr<Factory>>& getBuiltFactories();
	std::vector<std::shared_ptr<Factory>>& getDoneFactories();
	std::vector<std::shared_ptr<Factory>>& getStarvedFactories();
	std::vector<std::shared_ptr<Factory>>& getCombinedFactories();
	std::shared_ptr<Factory> getFactoryById(int id);
	Factory getFactoryByName(std::string name);

	static State* getInstance();
	static void destory();

};