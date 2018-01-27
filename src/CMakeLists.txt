cmake_minimum_required (VERSION 3.5)

project (sail-game)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)

# set (sail-game_VERSION_MAJOR 1)
# set (sail-game_VERSION_MINOR 0)

include_directories("${CMAKE_BINARY_DIR}/include")

FILE(GLOB SRC_FILES *.cpp)

add_executable(sail-game ${SRC_FILES})

set(COMPILE_OPTIONS "-std=c++11")
set(LINK_OPTIONS "-lGL")

target_compile_options(sail-game PUBLIC "${COMPILE_OPTIONS}")
target_link_libraries(sail-game "${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${LINK_OPTIONS}")

set_target_properties(sail-game
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
