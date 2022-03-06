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

	std::vector<Item> itemsState;
	std::vector<Technology> techonogiesState;
	std::vector<Factory> activeFactoriesState;
	std::vector<Factory> starvedFactoriesState;

public:
	

	bool checkIfRequirementIsFullfilled(std::vector<Item> requirements);
	bool checkIfTechnologyPrerequisitesIfFullfilled(vector<std::string> prerequisites);

	std::vector<Recipe> getPossibleRecipes();
	std::vector<Technology> getPossibleTechnology();

	std::vector<Item> getItemsState();
	std::vector<Technology> getTechonogiesState();
	std::vector<Factory> getActiveFactoriesState();
	std::vector<Factory> getStarvedFactoriesState();

	static State* getInstance();
	static void destory();

};