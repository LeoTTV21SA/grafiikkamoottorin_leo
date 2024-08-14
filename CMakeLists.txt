# Specify minimum supported cmake version
cmake_minimum_required(VERSION 3.5)

# set the project name
project(GraphicsProgramming1)
option(GLFW_BUILD_EXAMPLES "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_BUILD_DOCS "" OFF)
option(GLFW_INSTALL "" OFF)

add_subdirectory(ext/kgfw)
add_subdirectory(ext/glfw-3.3.2)
add_subdirectory(ext/glm-0.9.9.7)

# Specify include directories to include glad
include_directories("${GLFW_SOURCE_DIR}/deps")
include_directories("ext/stb-master")

include_directories("${GLFW_SOURCE_DIR}/deps")
set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h" "${GLFW_SOURCE_DIR}/deps/glad_gl.c")


# Define glad source files
set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h" "${GLFW_SOURCE_DIR}/deps/glad_gl.c")



# add the executables(glm example)
add_executable(glm_example main_glm_example.cpp)

target_link_libraries(glm_example PUBLIC glm)


# add the executable, which only uses single file "main.cpp"
add_executable(hello_world main_hello_world.cpp)

add_executable(math main_math.cpp)
target_link_libraries(math PUBLIC glm)

add_executable(glfw_window main_glfw_window.cpp ${GLAD_GL})
target_link_libraries(glfw_window PUBLIC kgfw PUBLIC glfw PUBLIC glm)

add_executable(draw_plane main_draw_plane.cpp ${GLAD_GL})
target_link_libraries(draw_plane PUBLIC kgfw PUBLIC glfw PUBLIC glm)

add_executable(shader_plane main_shader_plane.cpp shader.h shader.cpp plane.h gameobject.cpp plane.cpp ${GLAD_GL})
target_link_libraries(shader_plane PUBLIC kgfw PUBLIC glfw PUBLIC glm)

add_executable(color_plane main_color_plane.cpp shader.h shader.cpp plane.h gameobject.cpp plane.cpp ${GLAD_GL})
target_link_libraries(color_plane PUBLIC kgfw PUBLIC glfw PUBLIC glm)

add_executable(mvp main_mvp.cpp  shader.h shader.cpp plane.h plane.cpp gameobject.h gameobject.cpp camera.h ${GLAD_GL}) # recuerda poner en nombre ejecutable delante 
target_link_libraries(mvp PUBLIC kgfw PUBLIC glfw PUBLIC glm )

add_executable(painters_algorithm   main_painters_algorithm.cpp  shader.h shader.cpp plane.h plane.cpp gameobject.h gameobject.cpp camera.h ${GLAD_GL})
target_link_libraries(painters_algorithm PUBLIC kgfw PUBLIC glfw PUBLIC glm )

add_executable(depth_buffering main_depth_buffering.cpp shader.h shader.cpp plane.h plane.cpp gameobject.h gameobject.cpp camera.h ${GLAD_GL})
target_link_libraries(depth_buffering PUBLIC kgfw PUBLIC glfw PUBLIC glm )

add_executable(blending main_blending.cpp shader.h shader.cpp plane.h plane.cpp gameobject.h gameobject.cpp camera.h ${GLAD_GL})
target_link_libraries(blending PUBLIC kgfw PUBLIC glfw PUBLIC glm )

add_executable(simple_texturing main_simple_texturing.cpp shader.h shader.cpp plane.h plane.cpp gameobject.h gameobject.cpp camera.h ${GLAD_GL})
target_link_libraries(simple_texturing PUBLIC kgfw PUBLIC glfw PUBLIC glm )

add_executable(texture_loading main_texture_loading.cpp shader.h shader.cpp plane.h plane.cpp gameobject.h gameobject.cpp camera.h texture.h  texture.cpp ${GLAD_GL})
target_link_libraries(texture_loading PUBLIC kgfw PUBLIC glfw PUBLIC glm )

add_executable(sprite_batch main_spritebatch.cpp shader.h shader.cpp plane.h plane.cpp gameobject.h gameobject.cpp camera.h texture.h  texture.cpp spritebatch.h  spritebatch.cpp ${GLAD_GL})
target_link_libraries(sprite_batch PUBLIC kgfw PUBLIC glfw PUBLIC glm )




add_executable(practical_work main_practical_work.cpp shader.h shader.cpp plane.h plane.cpp gameobject.h gameobject.cpp camera.h texture.h texture.cpp spritebatch.h spritebatch.cpp player.cpp player.h ${GLAD_GL})
target_link_libraries(practical_work PUBLIC kgfw PUBLIC glfw PUBLIC glm )








