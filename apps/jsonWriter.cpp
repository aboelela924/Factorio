#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>

// event name :
// reaserch-event -> r_ev 
// build_factory -> b_fa_ev
// destroy_factory -> d_fa_ev
// start_factory -> str_fa_ev
// stop_factory -> stp_fa_ev
// victory_event -> v_ev
using nlohmann::json;

struct rEvent {
  int timestamp;
  std::string technology;
};

struct bFactoryEvent {
  int timestamp;
  int factoryID;
  std::string factoryType;
  std::string factoryName;
};

struct dFactoryEvent {
  int timestamp;
  int factoryID;
};


struct startFactoryEvent {
  int timestamp;
  int factoryID;
  std::string recipe;

};


struct stopFactoryEvent {
  int timestamp;
  int factoryID;
};


struct vEvent {
  int timestamp;
};



void to_json(json& j, const rEvent&  e)
{
    j = json{ {"type","research-event"},{"timestamp", e.timestamp}, {"technology", e.technology} };
}

void to_json(json& j, const bFactoryEvent&  e)
{
    j = json{ {"type","build-factory-event"},{"timestamp", e.timestamp}, {"factory-id",e.factoryID},{"factory-type", e.factoryType},{"factory-name", e.factoryName} };
}
void to_json(json& j, const dFactoryEvent&  e)
{
    j = json{ {"type","destroy-factory-event"},{"timestamp", e.timestamp}, {"factory-id",e.factoryID} };
}
void to_json(json& j, const startFactoryEvent&  e)
{
    j = json{ {"type","start-factory-event"},{"timestamp", e.timestamp}, {"factory-id",e.factoryID},{"recipe",e.recipe} };
}
void to_json(json& j, const stopFactoryEvent&  e)
{
    j = json{ {"type","stop-factory-event"},{"timestamp", e.timestamp}, {"factory-id",e.factoryID} };
}
void to_json(json& j, const vEvent&  e)
{
    j = json{ {"type","victory-event"},{"timestamp", e.timestamp}};
}

int main(){
    startFactoryEvent e1{0,0, "coal"};
    stopFactoryEvent e2{60, 0};
    vEvent e3{60};

    json j;
    j.push_back(e1);
    j.push_back(e2);
    j.push_back(e3);


    std::ofstream o("test_out.json");
    o << std::setw(4) << j << std::endl;
    
    return 0;
}
