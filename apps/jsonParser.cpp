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
			// std::cout << "item : "<< item.key() << "\n";
			// question : diff beetwen new and without ?
        	Item new_item =Item(item.key());
        	items.push_back(new_item);
        	// for (const auto& val : item.value().items())
        	// {
        	//     std::cout << " type :  " << val.value() << "\n";
        	// }
        	std::cout <<"----------------------"<<endl;
    		}
    return items;
	};


	std::vector<Recipe> static readRecipe(string path){
		std::vector<Recipe> recipes;
		std::ifstream i1(path);
		json recipeFile;
		i1 >> recipeFile;
		for (const auto& item : recipeFile.items()){
        std::cout << "recipe name : "<< item.key() << "\n";
        // std::cout<< recipeFile[item.key()]<<std::endl;

        // create ingredients
        std::cout<<"***ING__START***"<<std::endl;
        if(recipeFile[item.key()]["ingredients"].empty()==1)
            {
            // std::cout <<"check if empty --- > " <<recipeFile[item.key()]["ingredients"].empty()<< std::endl;
            std::cout <<"check if empty --- > " <<recipeFile[item.key()]["ingredients"]<< std::endl;

            std::cout<<"*****_*****_***"<<std::endl;

            for (const auto& ingredientItem : recipeFile[item.key()]["ingredients"][0].items())
                {
                    std::cout << ingredientItem.key() << ingredientItem.value() << std::endl;
                }
            }
        std::cout<<"***ING___END***"<<std::endl;

		for (const auto& item : recipeFile["ingredients"].items()) {
			// std::string factoryName = item.value()["factory-name"];
			// std::string factoryType = item.value()["factory-type"];
			// int factoryId = item.value()["factory-id"];
			// Factory f = Factory(factoryName, factoryType, factoryId);
			// initialFactories.push_back(f);
			std::cout << "Ingredient name is : " << item <<std::endl;
			std::cout<<"/-----/-/-/-/"<<std::endl;
		}

		std::cout<<"hohoooo : "<<recipeFile[item.key()]["ingredients"]<<std::endl;



        //create products

        //finaly create Recipe


        // Item* new_item =new Item(item.key());
        // items.push_back(new_item);
        // for (const auto& val : item.value().items())
        // {
        //     std::cout << val.key() << " : " << val.value() << "\n";
        // }
        std::cout <<"----------------------"<<std::endl;

		}	
		return recipes;
	}
};