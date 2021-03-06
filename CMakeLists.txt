cmake_minimum_required(VERSION 3.18.4)

project(PianoTiles)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS code/*.cpp)

add_executable("${PROJECT_NAME}" ${SOURCES})

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

# Set to use C++17
set_target_properties(
	"${PROJECT_NAME}"
	PROPERTIES
	CXX_STANDARD 17
	)

find_package(Thor 2 REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
find_package(TGUI 0.9 REQUIRED)

target_compile_options(
	"${PROJECT_NAME}" PRIVATE
	-Wall -Wextra -pedantic -Og
	)

target_include_directories(
	"${PROJECT_NAME}" PRIVATE
	"${YAML_CPP_INCLUDE_DIR}"
	"${THOR_INCLUDE_DIR}"
	header
	)

target_link_libraries(
	"${PROJECT_NAME}"
	PRIVATE
	"${YAML_CPP_LIBRARIES}"
	"${THOR_LIBRARY_RELEASE}"
	sfml-graphics
	sfml-window
	sfml-system
	tgui
	spdlog::spdlog
	)
