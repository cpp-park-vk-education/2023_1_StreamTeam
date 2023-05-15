set(PROJECT_SOURCES
        main.cpp

        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        authwindow.cpp
        authwindow.h
        authwindow.ui

        playerwindow.cpp
        playerwindow.h
        playerwindow.ui

)

add_executable(SyncView
    ${PROJECT_SOURCES}
)

add_compile_options(-Wall -Werror -Wpedantic -Wextra)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

target_link_libraries(SyncView PRIVATE Qt5::Widgets)

target_link_libraries(SyncView PRIVATE
    businesslogic
    Qt5::Widgets
)

set_target_properties(SyncView PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
