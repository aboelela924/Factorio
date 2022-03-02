#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

#include "model/factory.h"
#include "model/challenge.h"
#include "model/item.h"
#include "model/recipe.h"
#include "model/technology.h"



using json = nlohmann::json;
using namespace std;

class JsonParser {
public:
	Challenge static readChallenge(string path) {
		std::ifstream ifs(path);
		json jf;
		ifs >> jf;

		std::vector<Item> initialItems;
		std::vector<Item> goalItems;
		std::vector<Factory> initialFactories;

		for (const auto& item : jf["initial-items"].items()) {
			std::string name = item.value()["name"];
			int amount = item.value()["amount"] ;
			Item i = Item(name, amount);
			initialItems.push_back(i);
		}

		for (const auto& item : jf["goal-items"].items()) {
			std::string name = item.value()["name"];
			int amount = item.value()["amount"];
			Item i = Item(name, amount);
			goalItems.push_back(i);
		}

		for (const auto& item : jf["initial-factories"].items()) {
			std::string factoryName = item.value()["factory-name"];
			std::string factoryType = item.value()["factory-type"];
			int factoryId = item.value()["factory-id"];
			Factory f = Factory(factoryName, factoryType, factoryId);
			initialFactories.push_back(f);
		}

		Challenge c = Challenge(initialFactories, goalItems, initialItems);

		return c;

	}

	std::vector<Factory> static readFactories(string path) {
		std::vector<Factory> factories;
		std::ifstream ifs(path);
		json jf;

		ifs >> jf;

		for (const auto& item : jf.items()) {
			std::string name = item.key();
			double craftingSpeed = jf[item.key()]["crafting_speed"];
			std::vector<std::string> craftingCategories;
			for (const auto& category : jf[item.key()]["crafting_categories"].items()) {
				craftingCategories.push_back(category.key());
			}
			Factory factory = Factory(name, craftingSpeed, craftingCategories);
			factories.push_back(factory);
		}
		return factories;
	}

	std::vector<Item> static readItems(string path) {
		std::vector<Item> items;
		std::ifstream i1(path);
		json itemsFiles;
		i1 >> itemsFiles;
		for (const auto& item : itemsFiles.items()){
			std::string key = item.key();
			std::string type = item.value()["type"];
			Item i = Item(key, type);
			items.push_back(i);
    		}
    return items;
	};


	std::vector<Recipe> static readRecipe(string path){
		std::vector<Recipe> recipes;
		std::ifstream i1(path);
		json recipeFile;
		i1 >> recipeFile;
		for (const auto& recipe : recipeFile.items()) {
			std::string name = recipe.key();
			std::string category = recipe.value()["category"];
			bool enabled = recipe.value()["enabled"];
			int energy = recipe.value()["energy"];

		}
		return recipes;
	}

	std::vector<Technology> static readTechnology(string path) {
		std::ifstream ifs(path);
		json jf;
		ifs >> jf;

		std::vector<Technology> technologies;

		for (const auto& item : jf.items()) {
			std::string name;
			std::vector<std::string> prerequisites;
			std::vector<Item> ingredients;
			std::vector<std::string> effectes;
			bool enabled;


			name = item.key();
			enabled = false;

			for (const auto& effect : jf[name]["effects"].items()) {
				effectes.push_back(effect.value()["recipe"]);
			}

			for (const auto& ingredient : jf[name]["ingredients"].items()) {
				std::string itemName = ingredient.value()["name"];
				int amount = ingredient.value()["amount"];
				Item item = Item(itemName, amount);
				ingredients.push_back(item);
			}

			for (const auto& technology : jf[name]["prerequisites"].items()) {
				prerequisites.push_back(technology.value());
			}

			Technology tech = Technology(name, prerequisites, ingredients, effectes, enabled);
			technologies.push_back(tech);

		}

		return technologies;

	}
};