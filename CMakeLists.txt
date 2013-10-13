CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

PROJECT(qawale-core)

SET(EXECUTABLE_OUTPUT_PATH bin)
SET(LIBRARY_OUTPUT_PATH lib)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5Core)

INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/inc
)

SET(${PROJECT_NAME}_HEADERS
	inc/AI.hpp
	inc/APlayer.hpp
	inc/EasyAI.hpp
	inc/Gameboard.hpp
	inc/Game.hpp
	inc/HardAI.hpp
	inc/Hole.hpp
	inc/Player.hpp
)

SET(${PROJECT_NAME}_SOURCES
	src/AI.cpp
	src/APlayer.cpp
	src/EasyAI.cpp
	src/Gameboard.cpp
	src/Game.cpp
	src/HardAI.cpp
	src/Hole.cpp
	src/Player.cpp
)

ADD_LIBRARY(
	${PROJECT_NAME}
	SHARED
	${${PROJECT_NAME}_HEADERS}
	${${PROJECT_NAME}_SOURCES}
)

QT5_USE_MODULES(${PROJECT_NAME} Core)
