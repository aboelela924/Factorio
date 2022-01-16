set(
    SOURCES_AHMED 
    model/startFactoryEvent.cpp 
    model/stopFactoryEvent.cpp 
    model/victoryEvent.cpp 
    model/buildFactoryEvent.cpp 
    model/destoryFactoryEvent.cpp
    model/event.cpp
    model/researchEvent.cpp
    )
set(SOURCES_OSAMA )
set(SOURCES_OMAR
    model/technology.cpp
    model/prerequisite.cpp
    model/effect.cpp
    model/ingredient.cpp
    model/recipe.cpp
    model/item.cpp
)
add_executable(factorio factorio.cpp ${SOURCES_OMAR} ${SOURCES_AHMED} ${SOURCES_OUSAMA})

target_compile_features(factorio PRIVATE cxx_std_20)

target_link_libraries(factorio PRIVATE nlohmann_json::nlohmann_json)
