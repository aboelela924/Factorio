#include <nlohmann/json.hpp>
#include <fstream>

#include "model/factory.h"
#include "model/challenge.h"
#include "model/item.h"

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

};