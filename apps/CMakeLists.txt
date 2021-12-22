set(SOURCES_AHMED "model/startFactoryEvent.h" "model/stopFactoryEvent.h" "model/victoryEvent.h" "model/startFactoryEvent.cpp" "model/stopFactoryEvent.cpp")
set(SOURCES_OSAMA )
set(SOURCES_OMAR module/Date.cpp)
add_executable(factorio factorio.cpp ${SOURCES_OMAR} ${SOURCES_AHMED} ${SOURCES_OUSAMA})

target_compile_features(factorio PRIVATE cxx_std_20)

target_link_libraries(factorio PRIVATE nlohmann_json::nlohmann_json)
