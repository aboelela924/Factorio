#include "jsonParser.h"

Challenge JsonParser::readChallenge(string path)
{
	std::ifstream ifs(path);
	json jf;
	ifs >> jf;

	std::vector<Item> initialItems;
	std::vector<Item> goalItems;
	std::vector<Factory> initialFactories;

	for (const auto& item : jf["initial-items"].items()) {
		std::string name = item.value()["name"];
		int amount = item.value()["amount"];
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

std::vector<Factory> JsonParser::readFactories(string path)
{
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

std::vector<Item> JsonParser::readItems(string path)
{
	std::vector<Item> items;
	std::ifstream i1(path);
	json itemsFiles;
	i1 >> itemsFiles;
	for (const auto& item : itemsFiles.items()) {
		std::string key = item.key();
		std::string type = item.value()["type"];
		Item i = Item(key, type);
		items.push_back(i);
	}
	return items;
}

std::vector<Recipe> JsonParser::readRecipe(string path)
{
	std::vector<Recipe> recipes;
	std::ifstream i1(path);
	json recipeFile;
	i1 >> recipeFile;
	for (const auto& recipe : recipeFile.items()) {

		std::string name = recipe.key();
		std::string category = recipe.value()["category"];
		bool enabled = recipe.value()["enabled"];
		int energy = recipe.value()["energy"];

		std::vector<Item> ingredients;
		for (const auto& ingredient : recipe.value()["ingredients"].items()) {
			std::string name = ingredient.value()["name"];
			int amount = ingredient.value()["amount"];
			Item i = Item(name, amount);
			ingredients.push_back(i);
		}

		std::vector<Item> products;
		for (const auto& product : recipe.value()["products"].items()) {
			std::string name = product.value()["name"];
			int amount = product.value()["amount"];
			Item i = Item(name, amount);
			products.push_back(i);
		}

		Recipe r = Recipe(name, category, energy, enabled, ingredients, products);
		recipes.push_back(r);
	}
	return recipes;
}

std::vector<Technology> JsonParser::readTechnology(string path)
{
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

// void JsonParser::testFunction(std::map<string,string>& event){
// 	std::cout << "64661";
// 	auto it = event.findForward('eventType');
// 	std::string eventT=it->second;
// 	static json j;
// }

void JsonParser::testFunction(std::vector<string>& event) {
	int cc = stoi(event[0]);
	json static j;
	// std::ofstream file("hello_out.json",std::ios_base::app);
	switch (cc) {
	case 1:    // string output;
    // ifstream myfile;
    // ofstream myfile2;

    // string STRING;
    // myfile.open ("test_out.json");


    // myfile >> STRING;
    // cout << STRING;
    // myfile.close();
	case 2:
		j.push_back(json{ {"type","start-factory-event"},{"timestamp", event[1]}, {"factory-id",event[2]},{"recipe",event[3]}});
		break;
	case 3:
		j.push_back(json{{"type","destroy-factory-event"},{"timestamp", event[1]}, {"factory-id",event[2]} });
		break;
	case 4:
		j.push_back(json{{"type","stop-factory-event"},{"timestamp", event[1]}, {"factory-id",event[2]} });
		break;
	case 5:
		j.push_back(json{{"type","research-event"},{"timestamp", event[1]}, {"technology",event[2]} });
		break;
	case 6:
		j.push_back(json{{"type","victory-event"},{"timestamp", event[1]} });
		break;
	case 7:
		std::ofstream o("test_out.json");
    	o << std::setw(4) << j << std::endl;
    	cout << std::setw(4) << j << std::endl;
	//default:
		// event type 4
	}
};