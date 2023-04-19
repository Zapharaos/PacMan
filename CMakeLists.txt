cmake_minimum_required(VERSION 3.22.1)

project(PacMan LANGUAGES CXX)

#Find SDL2 library
find_package(SDL2 REQUIRED)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# Add source files to executable target
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
		include/config/config.h
		include/config/visuals.h
		include/display/animation.h
		include/display/scoreBoard.h
		include/display/sprite.h
		include/display/window.h
		include/entity/entity.h
		include/entity/fruit.h
		include/entity/fruitObject.h
		include/entity/ghost.h
		include/entity/ghosts.h
		include/entity/ghostSpecial.h
		include/entity/movingEntity.h
		include/entity/pacman.h
		include/map/cell.h
		include/map/map.h
		include/map/position.h
		include/utils/container.h
		include/utils/json.hpp
		include/utils/timer.h
		include/utils/direction.h
		include/utils/utils.h
		include/game.h
		include/config/config.h
		src/display/animation.cpp
		src/display/scoreBoard.cpp
		src/display/window.cpp
		src/entity/entity.cpp
		src/entity/fruit.cpp
		src/entity/ghost.cpp
		src/entity/ghosts.cpp
		src/entity/ghostSpecial.cpp
		src/entity/movingEntity.cpp
		src/entity/pacman.cpp
		src/map/map.cpp
		src/map/position.cpp
		src/utils/timer.cpp
		src/utils/utils.cpp
		src/game.cpp
		src/main.cpp)

# Set C++ standard
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Target SDL2
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE "SDL_MAIN_HANDLED")
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

# Copy resources to build directory
file(COPY resources/pacman_sprites.bmp resources/pacman_map.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Set startup project for Visual Studio
if(MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()
