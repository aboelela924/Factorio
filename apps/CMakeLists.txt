add_executable(factorio factorio.cpp "model/startFactoryEvent.h" "model/stopFactoryEvent.h" "model/victoryEvent.h" "model/startFactoryEvent.cpp" "model/stopFactoryEvent.cpp")

target_compile_features(factorio PRIVATE cxx_std_20)

target_link_libraries(factorio PRIVATE nlohmann_json::nlohmann_json)
