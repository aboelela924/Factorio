#pragma once
#include <string>
#include <memory>
#include <unordered_set>
#include <map>
#include <math.h>

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

	State(std::string challengeName);
	State(const State& cc) {};
	~State() {};

	double currentTick = -1;
	std::vector<Recipe> recipesPool;
	std::vector<Technology> technologiesPool;
	std::vector<Factory> factoriesPool;
	std::vector<Item> itemsPool;
	std::vector<Item> goalItems;

	std::vector<int> idPool;
	
	std::map<std::string, int> accumlatedItemGeneration;
	std::vector<std::shared_ptr<Item>> itemsState;
	std::vector<std::shared_ptr<Technology>> techonogiesState;

	std::vector<std::shared_ptr<Factory>> builtFactories;
	std::vector<std::shared_ptr<Factory>> stoppedFactories;
	std::vector<std::shared_ptr<Factory>> starvedFactories;
	std::vector<std::shared_ptr<Factory>> runningFactories;
	
	std::map<std::string, int> itemAmount;
	std::map<std::string, int> factoryPerRecipe;

	std::map<std::string, std::vector<std::string>> productRecipeMap;
	std::map<std::string, std::vector<std::pair<std::string, int>>> itemIngredientMap;


public:

	void getGoalItems(){
		for(Item i : this->goalItems){
			cout << i.getName() << ":" <<i.getAmount() << endl;
    }
	}

	// bool condition(Item item)
	// {
	// 	if(item.getName()==this->goalItems[0].getName() && item.getAmount()>=this->goalItems[0].getAmount() ){
	// 		return true;
	// 		} else {
	// 		return false;
	// 	}	
	// }

	bool isGoalItemAchieved(){
		std::vector<Item>& goalItems = this->goalItems; 
		auto it  = find_if(this->itemsState.begin(), this->itemsState.end(),
		[&goalItems](std::shared_ptr<Item> item){

			if(item->getName()==goalItems[0].getName() && item->getAmount()>=goalItems[0].getAmount() ){
				// cout <<"Goal achieved : Yes " << endl;
				return true;
			} else {
				// cout <<"Goal achieved : No " << endl;
				return false;
		}	

		});
		if(it != this->itemsState.end()) {
			return true;
			} else {
			return false;
		}
	}
	
	double getCurrentTick();
	double getNextTick();
	void incrementTick();

	std::vector<Recipe>& getRecipePool();

	
	int getNumberOfFactoryForRecipe(std::string recipeName);

	void moveFactory(int factoryId, 
		std::vector<std::shared_ptr<Factory>>& from, 
		std::vector<std::shared_ptr<Factory>>& to);
	void deleteFactoryById(int id,
		std::vector<std::shared_ptr<Factory>>& from);
	void addStarvedFactory(std::shared_ptr<Factory> f);
	

	Technology& getTechnologyByName(std::string name);

	void addItemToAccumlationMap(std::string name, int amount);
	int getItemAccumlatedAmount(std::string name);

	void backtrackRecipesForGoalItem(Challenge& c, 
		std::string pathToRecipes, 
		std::string pathToTechnologies);
	void getParent(Item& item, int factor, 
		std::vector<Recipe>& smallRecipePool, 
		std::vector<Technology>& smallTechnologyPool,
		std::unordered_set<std::string>& usedRecipesNames,
		std::unordered_set<std::string>& usedTechnologiesNames);
	Recipe getRecipeForItem(std::string name);
	void technologyPrerequisites(Technology& t, 
		std::vector<Recipe>& smallRecipePool,
		std::vector<Technology>& smallTechnologyPool,
		std::unordered_set<std::string>& usedRecipesNames,
		std::unordered_set<std::string>& usedTechnologiesNames);

	void calcFactoryPerRecipe();

	Technology& getTechnologyForRecipe(std::string name);
	int getItemAmount(std::string itemName);

	bool checkIfRequirementIsFullfilled(std::vector<Item> requirements);
	bool checkIfTechnologyPrerequisitesIfFullfilled(vector<std::string> prerequisites);

	Recipe getRecipeByName(std::string name);
	std::vector<Recipe> getPossibleRecipes();

	std::shared_ptr<Item> getItemByName(std::string name);
	std::shared_ptr<Item> getItemByNameFromItemPool(std::string name);

	std::vector<std::shared_ptr<Factory>>& getStoppedFactories();

	std::vector<Technology> getPossibleTechnology();

	std::vector<std::shared_ptr<Item>>& getItemsState();
	std::vector<std::shared_ptr<Technology>>& getTechonogiesState();

	void addBuiltFactories(Factory newFactory);
	int getNewFactoryId();
	void addFactoryIdToIdPool(int id);
	std::vector<Factory> getFactoryPool();
	std::vector<std::shared_ptr<Factory>>& getBuiltFactories();
	std::vector<std::shared_ptr<Factory>>& getStarvedFactories();
	std::vector<std::shared_ptr<Factory>>& getRunningFactories();
	std::vector<std::shared_ptr<Factory>> getCombinedFactories();
	std::shared_ptr<Factory> getFactoryById(int id);
	//void moveToRunningFactoryById(int id);
	Factory getFactoryByName(std::string name);

	static State* getInstance();
	static State* getInstance(std::string pathToChal);
	static void destory();

};