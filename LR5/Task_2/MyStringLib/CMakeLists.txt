cmake_minimum_required(VERSION 3.14)

project(MyStringLib LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(MyStringLib SHARED
  MyStringLib_global.h
  mystringlib.cpp
  mystringlib.h
)

target_link_libraries(MyStringLib PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(MyStringLib PRIVATE MYSTRINGLIB_LIBRARY)

target_include_directories(MyStringLib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include/MyStringLib>
)

# --- Опционально: правила установки ---
install(TARGETS MyStringLib
    LIBRARY       DESTINATION lib       # .so/.dylib
    RUNTIME       DESTINATION bin       # .dll
    ARCHIVE       DESTINATION lib       # .lib on Windows
    PUBLIC_HEADER DESTINATION include/MyStringLib
)

# Установим заголовки
install(FILES
    mystringlib.h
    MyStringLib_global.h
    DESTINATION include/MyStringLib
)
