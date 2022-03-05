#include "master.h"


Master::Master()
{
	state = State::getInstance();
	state->getPossibleRecipes();
	state->getPossibleRecipes();
}

Master::~Master()
{
	state->destory();
}


