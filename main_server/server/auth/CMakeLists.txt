add_library(auth src/auth.cpp)
target_include_directories(auth PUBLIC include)
target_link_libraries(auth PUBLIC session response)