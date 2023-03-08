cmake_minimum_required(VERSION 3.14)

project(PacMan LANGUAGES CXX)


find_package(SDL2 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(${PROJECT_NAME} ""
		include/entity/entity.h
		include/entity/fruit.h
		include/entity/ghost.h
		include/entity/movingEntity.h
		include/entity/pacman.h

		include/map/cell.h
		include/map/map.h

		include/sprite/extractor.h
		include/sprite/sprite.h

		include/utils/constants.h
		include/utils/json.hpp
		include/utils/timer.h

		include/game.h
		include/saveGame.h
		include/display/scoreBoard.h
		include/display/window.h
        src/utils/direction.cpp include/utils/direction.h)

target_sources(${PROJECT_NAME} PRIVATE

		src/entity/entity.cpp
		src/entity/fruit.cpp
		src/entity/ghost.cpp
		src/entity/movingEntity.cpp
		src/entity/pacman.cpp

		src/map/cell.cpp
		src/map/map.cpp

		src/sprite/extractor.cpp
		src/sprite/sprite.cpp

		src/utils/timer.cpp

		src/game.cpp
		src/main.cpp
		src/saveGame.cpp
        src/display/scoreBoard.cpp
        src/display/window.cpp

		)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE "SDL_MAIN_HANDLED")
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

file(COPY
		resources/pacman_sprites.bmp
		resources/pacman_map.txt
		DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

IF (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
ENDIF()
