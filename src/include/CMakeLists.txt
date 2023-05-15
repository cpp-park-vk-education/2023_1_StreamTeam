set(INCLUDE_SOURCES
        src/user.cpp
        inc/user.hpp
)

add_library(businesslogic STATIC
    ${INCLUDE_SOURCES}
)

target_link_libraries(businesslogic PRIVATE Qt5::Core)

target_include_directories(businesslogic INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(businesslogic PUBLIC inc)
