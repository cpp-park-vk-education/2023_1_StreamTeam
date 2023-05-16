set(INCLUDE_SOURCES
    src/user.cpp
    src/room.cpp
    src/message.cpp
    src/player.cpp
    src/serializer.cpp

    include/user.hpp
    include/room.hpp
    include/message.hpp
    include/player.hpp
    include/serializer.hpp
)

add_library(businesslogic STATIC
    ${INCLUDE_SOURCES}
)

# add_subdirectory(tests)

target_link_libraries(businesslogic PRIVATE Qt5::Core)

target_include_directories(businesslogic INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(businesslogic PUBLIC include)


