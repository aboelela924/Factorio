#pragma once
#include <string>
#include <memory>
#include <vector>
#include <bits/stdc++.h>
#include <map>

#include "state.h"
#include "events/event.h"
#include "events/factoryEvent.h"
#include "events/researchEvent.h"
#include "events/buildFactoryEvent.h"
#include "events/destoryFactoryEvent.h"
#include "events/startFactoryEvent.h"
#include "events/stopFactoryEvent.h"
#include "events/victoryEvent.h"
#include "model/factory.h"

class Master{
public:
	Master();
	~Master();
	
	std::shared_ptr<Factory> getFactoryForRecipe(std::string category);
	void startFactoryEvent(std::shared_ptr<Factory> factory, Recipe recipe);
	std::vector<Recipe>& getNewRecipes(const std::vector<Recipe>& recipes);
	void getFactoryEventForNewRecipe(const Recipe& r);
	void eventDone(FactoryEvent& event);
private:
	State* state;
	std::vector<std::shared_ptr<FactoryEvent>> activeFactoryEvents;
	std::vector<std::shared_ptr<FactoryEvent>> starvedFactoryEvents;
	std::map<int, std::vector<double>> factoryTimeMapping;

	class MyHashFunction {
	public:

		// We use predefined hash functions of strings
		// and define our hash function as XOR of the
		// hash values.
		size_t operator()(const Recipe& p) const
		{
			return (hash<string>()(p.name)) ^ (hash<string>()(p.categorie));
		}
	};
	std::unordered_set<Recipe, MyHashFunction> usedRecipes;

};
