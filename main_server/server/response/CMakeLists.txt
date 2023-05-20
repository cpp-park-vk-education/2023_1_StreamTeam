add_library(response src/response.cpp)
target_include_directories(response PUBLIC include)
target_link_libraries(response PUBLIC message)