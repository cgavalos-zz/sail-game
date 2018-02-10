cmake_minimum_required (VERSION 3.5)

add_executable(sail-game main.cpp)

target_sources(sail-game PUBLIC
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
  Triangle.cpp
  Mesh.cpp
  PointForce.cpp
  SkyParameters.cpp
  WindowParameters.cpp
  SkyboxObject.cpp
  Plane.cpp
)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(sail-game
  ${SDL2_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${OPENGL_gl_LIBRARY}
)

target_compile_features(sail-game
  PUBLIC
    cxx_nullptr
)

set_target_properties(sail-game
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
)
