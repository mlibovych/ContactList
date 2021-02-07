cmake_minimum_required(VERSION 3.18.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -pipe -Wall -Wextra -Wpedantic -Wno-unused-parameter")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(TARGET contactlist)

find_package(Qt5 COMPONENTS Widgets Sql Multimedia REQUIRED)

set(SOURCES src/main.cpp src/mediator.cpp src/mainwindow.cpp 
            src/component.cpp src/contact_list_provider.cpp
            src/contact_list_provider.cpp src/general_screen.cpp src/new_contact_screen.cpp
            src/contact_widget.cpp)

set(INCLUDES inc/mediator.h inc/mainwindow.h inc/component.h 
             inc/contact_list_provider.h inc/contact_list_provider.h inc/general_screen.h
             inc/new_contact_screen.h inc/contact_widget.h inc/contact.h)

qt5_add_resources(SOURCES resources/resources.qrc)

include_directories(inc)

add_executable(${TARGET} ${SOURCES} ${INCLUDES})

target_link_libraries(${TARGET} Qt5::Core Qt5::Widgets Qt5::Sql Qt5::Multimedia)

set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../..)
