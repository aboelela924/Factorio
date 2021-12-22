set (JHDHKD ...CPP)
add_executable(factorio factorio.cpp module/Date.cpp)


target_compile_features(factorio PRIVATE cxx_std_20)

target_link_libraries(factorio PRIVATE nlohmann_json::nlohmann_json)
