add_library(userinterface src/message.cpp src/player.cpp src/room.cpp src/user.cpp src/serializer.cpp)

target_include_directories(userinterface PUBLIC include)