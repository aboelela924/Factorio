#include "researchEvent.h"


ResearchEvent::ResearchEvent(double timestamp, string technology) 
	: Event{ timestamp }, technology(technology) { };

void ResearchEvent::run() {

	vector<string> event={"5",to_string(this->getTimestamp()),technology};
	JsonParser::testFunction(event);


	State* state = State::getInstance();
	Technology& t = state->getTechnologyByName(this->technology);

	t.setEnabled(true);

	std::cout << "At timestamp: " << this->timestamp << "Technology: " << t.getName() << " was enabled.\n";

	for (Item i : t.getIngredients()) {
		state->getItemByName(i.getName())->decreaseAmountBy(i.getAmount());
	}

	for (std::string recipeName : t.getEffects()) {
		/*Recipe r = state->getRecipeByName(recipeName);
		if (r != state->getRecipePool().end()) {

		}*/
		std::vector<Recipe>& recipePool = state->getRecipePool();
		auto it = find_if(recipePool.begin(), recipePool.end(),
			[&recipeName](Recipe r) {return r.getName() == recipeName; });

		if (it != recipePool.end()) {
			(*it).setEnabled(true);
			std::cout << "At timestamp: " << this->timestamp << "Recipe: " << (*it).getName() << " was enabled.\n";
		}
	}

}

std::string ResearchEvent::getTechnologyName()
{
	return this->technology;
}
