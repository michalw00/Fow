cmake_minimum_required(VERSION 3.0)
project(Fow)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/raylib)
add_subdirectory(external/raylib_cpp)

file(GLOB_RECURSE RAYLIB_CPP_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/external/raylib_cpp/include/*.hpp)
add_custom_target(raylib_cpp_sources SOURCES ${RAYLIB_CPP_HEADERS})

set(SOURCE_LIST
src/main.cc

src/match/match.h
src/match/match.cc   	
src/match/player.h 
src/match/player.cc
src/match/map/map.h
src/match/map/map.cc
src/match/map/tile.h
src/match/map/tile.cc
	
	
src/core/core.h
src/core/core.cc

src/core/screen/screen.h
src/core/screen/menu_screen.h
src/core/screen/menu_screen.cc


src/input/input.h
src/input/input.cc
	
)

add_executable(Fow ${SOURCE_LIST})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/external/raylib_cpp/include FILES ${RAYLIB_CPP_HEADERS})

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "Fow")

target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp)
