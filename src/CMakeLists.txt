cmake_minimum_required (VERSION 3.5)

set(SRC_FILES
  World.cpp
  RigidObject.cpp
  TestObject.cpp
  FileUtils.cpp
  PlayerInputComponent.cpp
  SkyboxObjectGraphicsComponent.cpp
  ShaderMisc.cpp
  WaterSurfacePhysicsComponent.cpp
  RigidObjectGraphicsComponent.cpp
  Line.cpp
  UBOManager.cpp
  WaterSurface.cpp
  Camera.cpp
  Player.cpp
  VertexElementGraphicsComponent.cpp
  TypeSize.cpp
  WaterSurfaceGraphicsComponent.cpp
  RigidBody.cpp
  main.cpp
  Triangle.cpp
  Mesh.cpp
  PointForce.cpp
  SkyParameters.cpp
  WindowParameters.cpp
  SkyboxObject.cpp
  Plane.cpp)

add_executable(sail-game ${SRC_FILES})

set(COMPILE_OPTIONS -std=c++11)
set(LINK_OPTIONS -lGL)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)

target_compile_options(sail-game PUBLIC ${COMPILE_OPTIONS})
target_link_libraries(sail-game ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${LINK_OPTIONS})

set_target_properties(sail-game
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
