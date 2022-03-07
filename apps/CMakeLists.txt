set(
    SOURCES_AHMED 
    events/startFactoryEvent.cpp 
    events/stopFactoryEvent.cpp 
    events/victoryEvent.cpp 
    events/buildFactoryEvent.cpp 
    events/destoryFactoryEvent.cpp
    events/event.cpp
    events/researchEvent.cpp
    master.cpp
    state.cpp
    utils.cpp)
set(SOURCES_OSAMA )
set(SOURCES_OMAR
    model/technology.cpp
    
    
    
    
    model/recipe.cpp
    model/item.cpp
)
add_executable(factorio factorio.cpp ${SOURCES_OMAR} ${SOURCES_AHMED} ${SOURCES_OUSAMA} "model/factory.h" "model/challenge.h" "model/challenge.cpp" "master.h" "master.cpp" "state.h"  "jsonParser.h")

target_compile_features(factorio PRIVATE cxx_std_20)

target_link_libraries(factorio PRIVATE nlohmann_json::nlohmann_json)
