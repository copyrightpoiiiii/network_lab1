cmake_minimum_required(VERSION 3.15)
project(network_lab1)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)


set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.12.3/lib/cmake")

set(QT Core Gui Widgets)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

aux_source_directory(. DIRS_SRCS)

add_executable(network_lab1 ${DIRS_SRCS})

target_link_libraries(network_lab1 Qt5::Widgets)
target_link_libraries(network_lab1 Qt5::Core)
target_link_libraries(network_lab1 Qt5::Gui)

qt5_use_modules(network_lab1 ${QT})


