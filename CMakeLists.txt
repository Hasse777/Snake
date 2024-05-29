cmake_minimum_required(VERSION 3.14)

project(Snake LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Snake
  main.cpp
  mainWindow.h
  mainWindow.cpp
  gameField.h
  gameField.cpp
  snake.h
  snake.cpp
  hintField.h
  hintField.cpp
  resources.qrc
)
target_link_libraries(Snake PRIVATE Qt6::Widgets)

include(GNUInstallDirs)
install(TARGETS Snake
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
