cmake_minimum_required(VERSION 3.14)

project(PacMan LANGUAGES CXX)


find_package(SDL2 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
add_executable(${PROJECT_NAME} ""
		include/utils/constants.h
		include/map/map.h
		include/map/cell.h
		include/game.h
		include/entity/ghost.h
        include/entity/entity.h
		include/entity/powerUp.h

 		include/scoreBoard.h
		include/saveGame.h
		include/utils/json.hpp include/sprite/extractor.h src/entity/movingEntity.cpp include/entity/movingEntity.h src/entity/pacman.cpp include/entity/pacman.h src/sprite/sprite.cpp include/sprite/sprite.h src/window.cpp)

target_sources(${PROJECT_NAME} PRIVATE
        src/main.cpp
		src/map/map.cpp
		src/map/cell.cpp
		src/game.cpp
		src/entity/ghost.cpp
		src/entity/entity.cpp
		src/entity/powerUp.cpp
		src/scoreBoard.cpp
		src/saveGame.cpp
		src/sprite/extractor.cpp

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
