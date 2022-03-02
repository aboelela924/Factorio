
#include "model/event.h"
#include "model/researchEvent.h"
#include "model/buildFactoryEvent.h"
#include "model/destoryFactoryEvent.h"
#include "model/startFactoryEvent.h"
#include "model/stopFactoryEvent.h"
#include "model/victoryEvent.h"
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

    std::string local_path = getexepath();
    std::string delimiter = "out";
    local_path = local_path.substr(0, local_path.find(delimiter)); 
    std::string path=local_path+"jsons/example_1.json";
    std::cout << "PATH  : "<< path << std::endl;


    Master master = Master(local_path);

    

    return 0;

}
