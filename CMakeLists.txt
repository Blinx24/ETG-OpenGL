cmake_minimum_required(VERSION 3.14)
project(engine_flyingcamera_eventos)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})

add_executable(engine_flyingcamera_eventos Engine.cpp Teapot.cpp Teapot.h Vector3D.cpp Vector3D.h Cube.cpp Cube.h Sphere.cpp Sphere.h Color.cpp Color.h Camera.cpp Camera.h Scene.cpp Scene.h Cuboid.cpp Cuboid.h Torus.cpp Torus.h Cylinder.cpp Cylinder.h FlyingCamera.cpp FlyingCamera.h GameObject.cpp GameObject.h Game.cpp Game.h)
target_link_libraries(engine_flyingcamera_eventos ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
