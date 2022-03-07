#pragma once
#include <string>
#include <memory>

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

	std::vector<std::shared_ptr<Item>> itemsState;
	std::vector<std::shared_ptr<Technology>> techonogiesState;

	std::vector<std::shared_ptr<Factory>> notStartedFactoriesState;
	std::vector<std::shared_ptr<Factory>> activeFactoriesState;
	std::vector<std::shared_ptr<Factory>> starvedFactoriesState;

	

public:
	
	double getCurrentTick();
	void incrementTick();

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
	std::vector<std::shared_ptr<Factory>>& getNotStartedFactories();
	std::vector<std::shared_ptr<Factory>>& getActiveFactoriesState();
	std::vector<std::shared_ptr<Factory>>& getStarvedFactoriesState();
	std::shared_ptr<Factory> getFactoryById(int id);

	static State* getInstance();
	static void destory();

};