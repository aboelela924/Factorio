#pragma once
#include <string>
#include <memory>
#include <vector>
#include <bits/stdc++.h>
#include <map>
#include <typeinfo>

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

#include "feedback.h"

class Master : public Feedback {
public:
	Master();
	~Master();
	
	
	std::vector<Recipe> getNewRecipes(const std::vector<Recipe>& recipes);
	void getFactoryEventForNewRecipe(Recipe& r);
	void eventDone(FactoryEvent* e) override;
private:
	State* state;
	std::vector<std::shared_ptr<BuildFactoryEvent>> buildFactoryEvents;

	std::vector<std::shared_ptr<StartFactoryEvent>> activeFactoryEvents;
	std::vector<std::shared_ptr<StartFactoryEvent>> starvedFactoryEvents;
	std::vector<std::shared_ptr<StartFactoryEvent>> stoppFactoryEvents;

	template <class T> void sortFactoryEvents(std::vector<std::shared_ptr<T>>& v);
	void possibleCombinationOfEventsToRun();
	bool haveEnoughResources(std::map<std::string, int> ingredientsSum);
	void checkForFactoryToStop(FactoryEvent* e);


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

template<class T>
inline void Master::sortFactoryEvents(std::vector<std::shared_ptr<T>>& v)
{

	std::sort(v.begin(), v.end(),
		[](std::shared_ptr<T>& lhs, std::shared_ptr<T>& rhs)
		{
			return lhs->getFactoryId() < rhs->getFactoryId();
		});
}
