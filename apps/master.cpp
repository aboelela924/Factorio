#include "master.h"


Master::Master()
{
	state = State::getInstance();
	state->getPossibleRecipes();
	state->getPossibleTechnology();
}

Master::~Master()
{
	state->destory();
}


