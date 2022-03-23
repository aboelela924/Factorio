

#include "model/technology.h"
#include "model/recipe.h"
#include "model/factory.cpp"

#include "jsonParser.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

#include <nlohmann/json.hpp>

#include <string>
#include <limits.h>
#include <unistd.h>
#include "master.h"

    std::string getexepath()
    {
        char result[ PATH_MAX ];
        ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
        return std::string( result, (count > 0) ? count : 0 );
    }



using json = nlohmann::json;

int main(int argc, char** argv){
	// std::string mainPath = Utils::getexepath();
	// std::string delimiter = "Factorio";
	// mainPath = mainPath.substr(0, mainPath.find(delimiter));
    // mainPath+="Factorio";
	// std::string challengePath = mainPath + "/data/factorio-simulator/inputs/challenge-1.json";

	// std::cout<< "My path : " << challengePath;

    Master master = Master();

    return 0;

}
