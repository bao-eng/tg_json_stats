cmake_minimum_required(VERSION 3.0.0)
project(tg_json_stats VERSION 0.1.0)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
find_package(ICU COMPONENTS io i18n REQUIRED)
include_directories(${ICU_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR})

include(CTest)
enable_testing()

add_executable(tg_json_stats main.cpp tg_json_stats.cpp dict_opc.cpp)

target_link_libraries(tg_json_stats ${ICU_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


