#pragma once
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

#include "model/factory.h"
#include "model/challenge.h"
#include "model/item.h"
#include "model/recipe.h"
#include "model/technology.h"
#include <iomanip>



using json = nlohmann::json;
using namespace std;

class JsonParser
{
public:
	Challenge static readChallenge(string path);
	std::vector<Factory> static readFactories(string path);
	std::vector<Item> static readItems(string path);
	std::vector<Recipe> static readRecipe(string path);
	std::vector<Technology> static readTechnology(string path);
	void static testFunction(std::vector<string>& event);

};
