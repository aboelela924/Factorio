#pragma once
#include <string>
#include "state.h"

class Master {
public:
	Master();
	~Master();

private:
	State* state;
};
