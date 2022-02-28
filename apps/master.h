#pragma once
#include <string>
#include "model/recipe.h"
#include "model/factory.h"
#include "model/technology.h"
#include "model/item.h"

class Master {
public:
	Master(std::string path);

private:
	double currentTick = -1;

	std::vector<Recipe> recipesPool;
	std::vector<Technology> technologiesPool;
	std::vector<Factory> factoriesPool;
	std::vector<Item> itemsPool;

};
