cmake_minimum_required(VERSION 3.7)

project(PacMan LANGUAGES CXX)


find_package(SDL2 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
add_executable(${PROJECT_NAME} ""
		include/constants.h
		include/map.h
		include/cell.h
		include/game.h
		include/ghost.h
		include/entity.h
		include/powerUp.h

 		include/scoreBoard.h
		include/saveGame.h
		include/json.hpp  include/extractor.h src/movingEntity.cpp include/movingEntity.h src/pacman.cpp include/pacman.h src/sprite.cpp include/sprite.h)

target_sources(${PROJECT_NAME} PRIVATE
        src/main.cpp
		src/map.cpp
		src/cell.cpp
		src/game.cpp
		src/ghost.cpp
		src/entity.cpp
		src/powerUp.cpp
		src/scoreBoard.cpp
		src/saveGame.cpp
		src/extractor.cpp

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
