add_library(UserInterface 
                src/message.cpp 
                src/player.cpp 
                src/room.cpp 
                src/user.cpp 
                src/serializer.cpp 
            )

target_include_directories(UserInterface PUBLIC include)

add_subdirectory(tests)