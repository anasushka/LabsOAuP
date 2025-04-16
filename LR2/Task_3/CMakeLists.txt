cmake_minimum_required(VERSION 3.14)

project(Task_3 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(Task_3
  main.cpp
  expression.h expression.cpp
  number.h number.cpp
  binaryoperation.h binaryoperation.cpp
)
target_link_libraries(Task_3 Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS Task_3
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
