#include "state.h"
#include "utils.h"

State* State::instance = 0;

State::State(std::string challengeName) {
    //Omar
	std::string mainPath = Utils::getexepath();
	std::string delimiter = "Factorio";
	mainPath = mainPath.substr(0, mainPath.find(delimiter));
    mainPath+="Factorio";
	std::string challengePath =  challengeName;//"/data/factorio-simulator/inputs/"+challengeName;//challenge-3.json";
    // cout << "challengePath : " << challengePath << endl;
	Challenge challenge = JsonParser::readChallenge(challengeName);

    //Ahmed
    // std::string mainPath = Utils::getexepath();
	// std::string delimiter = "out";
	// mainPath = mainPath.substr(0, mainPath.find(delimiter));

	// std::string challengePath = mainPath + "/data/factorio-simulator/inputs/challenge-3.json";
	// Challenge challenge = JsonParser::readChallenge(challengePath);
    //------------------

    for(Item i : challenge.getGoalItems()){
        this->goalItems.push_back(i);
    }

	std::string recipesPath = mainPath + "/data/factorio-data/recipe.json";
	this->recipesPool = JsonParser::readRecipe(recipesPath);

	for (Recipe r : this->recipesPool) {
		for (Item i : r.getProducts()) {
			if (r.getName().find("barrel") == std::string::npos || r.getName() ==  "empty-barrel") {
				this->productRecipeMap[i.getName()].push_back(r.getName());
			}
		}
	}

	std::string itemsPath = mainPath + "/data/factorio-data/item.json";
	this->itemsPool = JsonParser::readItems(itemsPath);

	std::string factoriesPath = mainPath + "/data/factorio-data/factory.json";
	this->factoriesPool = JsonParser::readFactories(factoriesPath);

	std::string technologiesPath = mainPath + "/data/factorio-data/technology.json";
	this->technologiesPool = JsonParser::readTechnology(technologiesPath);

	this->backtrackRecipesForGoalItem(challenge, recipesPath, technologiesPath);
	this->calcFactoryPerRecipe();

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

		this->builtFactories.push_back(std::shared_ptr<Factory>(new Factory(f)));
	}

	for (int i = 1; i < 10000; ++i) {
		idPool.push_back(i);
	}
}


State* State::getInstance(std::string pathToChal) {
	if (!instance) {
		instance = new State(pathToChal);
	}
	return instance;
}

State* State::getInstance(){
    return instance;
}


double State::getCurrentTick()
{
	return this->currentTick;
}
double State::getNextTick()
{
	
	return this->currentTick + 1;
}
void State::incrementTick()
{
	
	this->currentTick += 1;
	
}

std::vector<Recipe>& State::getRecipePool()
{
	return this->recipesPool;
}


Technology& State::getTechnologyByName(std::string name)
{
	auto it = find_if(this->technologiesPool.begin(),
		this->technologiesPool.end(),
		[&name](Technology t) {return t.getName() == name; });
	return *it;
}

void State::addItemToAccumlationMap(std::string name, int amount)
{
	if (this->accumlatedItemGeneration.find(name) == this->accumlatedItemGeneration.end()) {
		this->accumlatedItemGeneration[name] = amount;
	}
	else {
		this->accumlatedItemGeneration[name] += amount;
	}

}

int State::getItemAccumlatedAmount(std::string name)
{
	if (this->accumlatedItemGeneration.find(name) != this->accumlatedItemGeneration.end()) {
		return this->accumlatedItemGeneration[name];
	}
	return 0;
}

Recipe State::getRecipeForItem(std::string name) {
	Recipe r = this->getRecipeByName(name);
	if (!r.getName().empty()) {
		return r;
	}


	vector<std::string> recipesNames = this->productRecipeMap[name];
	vector<Recipe> recipes;

	for (std::string recipeName : recipesNames) {
		Recipe r = this->getRecipeByName(recipeName);
		recipes.push_back(r);
	}


	std::sort(recipes.begin(), recipes.end(),
		[](Recipe s1, Recipe s2)
		{ return s1.getIngredients().size() < s2.getIngredients().size(); });
	return recipes[0];

}

void State::backtrackRecipesForGoalItem(Challenge& c, 
	std::string pathToRecipes, 
	std::string pathToTechnologies)
{

	std::vector<Recipe> smallRecipePool;
	std::vector<Technology> smallTechnologyPool;
	std::unordered_set<std::string> usedRecipesNames;
	std::unordered_set<std::string> usedTechnologiesNames;

	for (Item goal : c.getGoalItems()) {
		this->itemIngredientMap[goal.getName()] = std::vector<std::pair<std::string, int>>();

		getParent(goal, goal.getAmount(), smallRecipePool,
			smallTechnologyPool, usedRecipesNames, 
			usedTechnologiesNames);

		if (this->itemAmount.find(goal.getName()) == this->itemAmount.end()) {
			this->itemAmount[goal.getName()] = goal.getAmount();
		}
		else {
			this->itemAmount[goal.getName()] += goal.getAmount();
		}
	}


	this->recipesPool = smallRecipePool;
	this->technologiesPool = smallTechnologyPool;

	/*for (auto it = itemAmount.begin(); it != itemAmount.end(); ++it) {
		itemAmount[it->first] = ceil(it->second * 1.5);
	}*/

}

void State::getParent(Item& item, int factor,  
	std::vector<Recipe>& smallRecipePool, 
	std::vector<Technology>& smallTechnologyPool, 
	std::unordered_set<std::string>& usedRecipesNames, 
	std::unordered_set<std::string>& usedTechnologiesNames)
{

	
	
	Recipe r = this->getRecipeForItem(item.getName());

	for (Item i : r.getIngredients()) {

		int newFactor = factor * i.getAmount();
		getParent(i, newFactor, smallRecipePool,
			smallTechnologyPool, usedRecipesNames,
			usedTechnologiesNames);

		if (this->itemAmount.find(i.getName()) == this->itemAmount.end()) {
			this->itemAmount[i.getName()] = newFactor;
		}
		else {
			this->itemAmount[i.getName()] += newFactor;
		}
	}

	if (!r.getEnbaled()) {
		Technology t = getTechnologyForRecipe(r.getName());

		technologyPrerequisites(t, smallRecipePool,
			smallTechnologyPool, usedRecipesNames,
			usedTechnologiesNames);

	}

	if (usedRecipesNames.find(r.getName()) == usedRecipesNames.end()) {
		smallRecipePool.push_back(r);
		usedRecipesNames.insert(r.getName());
	}
}

void State::technologyPrerequisites(Technology& t, 
	std::vector<Recipe>& smallRecipePool, 
	std::vector<Technology>& smallTechnologyPool, 
	std::unordered_set<std::string>& usedRecipesNames, 
	std::unordered_set<std::string>& usedTechnologiesNames)
{

	for (Item i : t.getIngredients()) {
		getParent(i, i.getAmount(), smallRecipePool,
			smallTechnologyPool, usedRecipesNames,
			usedTechnologiesNames);

		if (this->itemAmount.find(i.getName()) == this->itemAmount.end()) {
			this->itemAmount[i.getName()] = i.getAmount();
		}
		else {
			this->itemAmount[i.getName()] += i.getAmount();
		}
	}

	if (usedTechnologiesNames.find(t.getName()) == usedTechnologiesNames.end() && !t.getName().empty()) {
		smallTechnologyPool.push_back(t);
		usedTechnologiesNames.insert(t.getName());

		for (std::string ingTechName : t.getPrerequisites()) {
			Technology& ingTech = this->getTechnologyByName(ingTechName);
			technologyPrerequisites(ingTech,
				smallRecipePool, smallTechnologyPool, usedRecipesNames, usedTechnologiesNames);
		}
	}


	

}

void State::calcFactoryPerRecipe()
{

	for (Recipe rOut : this->recipesPool ) {

		for (Item iOut : rOut.getProducts()) {
			for (Recipe rIng : this->recipesPool) {
				for (Item iIng : rIng.getIngredients()) {
					if (iOut.getName() == iIng.getName()) {
						auto it = factoryPerRecipe.find(rOut.getName());
						if (it == factoryPerRecipe.end()) {
							factoryPerRecipe[rOut.getName()] = 1;
						}
						else {
							factoryPerRecipe[rOut.getName()] += 1;
						}
					}
				}
			}
		}

		/*std::vector<Item>& ings = r.getIngredients();
		for (Item i : ings) {
			Recipe r = this->getRecipeForItem(i.getName());
			auto it = factoryPerRecipe.find(r.getName());
			if (it == factoryPerRecipe.end()) {
				factoryPerRecipe[r.getName()] = 1;
			}else{
				factoryPerRecipe[r.getName()] += 1;
			}
		}*/
	}

}

Technology& State::getTechnologyForRecipe(std::string name) {
	auto it = find_if(this->technologiesPool.begin(),
		this->technologiesPool.end(),
		[&name](Technology t) {
			for (std::string recipeNameToUnlock : t.getEffects()) {
				if (recipeNameToUnlock == name) {
					return true;
				}
			}
			return false;
		});
	int index = std::distance(this->technologiesPool.begin(), it);
	return this->technologiesPool[index];
}

int State::getItemAmount(std::string itemName)
{
	if (this->itemAmount.find(itemName) != this->itemAmount.end()) {
		return this->itemAmount[itemName];
	}

	return 0;
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
	this->builtFactories.push_back(std::shared_ptr<Factory>(new Factory(newFactory)));
}
std::vector<Factory> State::getFactoryPool()
{
	return this->factoriesPool;
}

void State::deleteFactoryById(int id, std::vector<std::shared_ptr<Factory>>& from)
{
	auto it = find_if(
		from.begin(), from.end(),
		[id](std::shared_ptr<Factory> f) {return f->getFactoryId() == id; }
	);
	if (it != from.end()) {
		from.erase(it);
	}
}
void State::addStarvedFactory(std::shared_ptr<Factory> f)
{
	this->starvedFactories.push_back(f);
}
int State::getNumberOfFactoryForRecipe(std::string recipeName)
{
	 

	return this->factoryPerRecipe[recipeName];
}
/*void State::moveToRunningFactoryById(int id)
{
	auto it = find_if(this->builtFactories.begin(),
		this->builtFactories.end(),
		[&id](std::shared_ptr<Factory> obj) {return obj->getFactoryId() == id; });
	if (it != this->builtFactories.end()) {
		this->runningFactories.push_back(*it);
		this->builtFactories.erase(it);
		return;
	}
	auto it = find_if(this->starvedFactories.begin(),
		this->starvedFactories.end(),
		[&id](std::shared_ptr<Factory> obj) {return obj->getFactoryId() == id; });
	if (it != this->starvedFactories.end()) {
		this->runningFactories.push_back(*it);
		this->starvedFactories.erase(it);
		return;
	}
}*/
void State::moveFactory(int factoryId, 
	std::vector<std::shared_ptr<Factory>>& from, 
	std::vector<std::shared_ptr<Factory>>& to)
{
	auto it = find_if(
		from.begin(), from.end(),
		[factoryId](std::shared_ptr<Factory> f) {return f->getFactoryId() == factoryId; }
	);
	if (it != from.end()) {
		to.insert(to.end(), *it);
		from.erase(it);
	}
}


std::vector<std::shared_ptr<Factory>>& State::getStoppedFactories()
{
	return this->stoppedFactories;
}
std::vector<std::shared_ptr<Factory>>& State::getStarvedFactories()
{
	return this->starvedFactories;
}
std::vector<std::shared_ptr<Factory>>& State::getRunningFactories()
{
	return this->runningFactories;
}
std::shared_ptr<Factory> State::getFactoryById(int id)
{
	
	std::vector<shared_ptr<Factory>> allFactories = std::vector<shared_ptr<Factory>>();
	
	allFactories.insert(allFactories.end(), this->builtFactories.begin(),
		this->builtFactories.end());
	
	allFactories.insert(allFactories.end(), this->runningFactories.begin(),
		this->runningFactories.end());

	allFactories.insert(allFactories.end(), this->starvedFactories.begin(), 
		this->starvedFactories.end());
	
	auto it = find_if(allFactories.begin(),
		allFactories.end(),
		[&id](std::shared_ptr<Factory> obj) {return obj->getFactoryId() == id; });
	if (it != allFactories.end()) {
		auto index = std::distance(allFactories.begin(), it);
		return allFactories[index];
	}



	return nullptr;
}
std::vector<std::shared_ptr<Factory>> State::getCombinedFactories()
{
	std::vector<std::shared_ptr<Factory>> factories = std::vector<std::shared_ptr<Factory>>();

	factories.insert(factories.end(), this->builtFactories.begin(),
		this->builtFactories.end());
	factories.insert(factories.end(), this->stoppedFactories.begin(), 
		this->stoppedFactories.end());
	factories.insert(factories.end(), this->starvedFactories.begin(), 
		this->starvedFactories.end());

	return factories;
}
std::vector<std::shared_ptr<Factory>>& State::getBuiltFactories()
{
	return this->builtFactories;
}
int State::getNewFactoryId() {
	std::sort(this->idPool.begin(), this->idPool.end());
	int id = this->idPool[0];
	this->idPool.erase(this->idPool.begin());
	return id;
}
void State::addFactoryIdToIdPool(int id)
{
	this->idPool.push_back(id);
}
Factory State::getFactoryByName(std::string name) {
	auto it = find_if(this->factoriesPool.begin(),
		this->factoriesPool.end(),
		[&name](Factory& obj) { return obj.getName() == name; });
	int index = std::distance(this->factoriesPool.begin(), it);
	return this->factoriesPool[index];
}



void State::destory() {
	delete instance;
	instance = NULL;
}