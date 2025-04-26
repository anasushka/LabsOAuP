cmake_minimum_required(VERSION 3.5)

project(Task_2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

add_subdirectory(MyStringLib)  # Подключаем подпроект MyStringLib

# Создаем исполняемый файл ДО настройки свойств и линковки
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Task_2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Task_2 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Task_2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Теперь таргет Task_2 существует, можно настраивать свойства
set_target_properties(Task_2 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Линкуем библиотеки после создания таргета
target_link_libraries(Task_2 PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    MyStringLib  # Предполагается, что MyStringLib создает таргет с таким именем
)

# Дополнительные настройки для macOS
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Task_2)
endif()

set_target_properties(Task_2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Установка и финализация (для Qt 6)
include(GNUInstallDirs)
install(TARGETS Task_2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Task_2)
endif()
