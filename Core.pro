#-------------------------------------------------
#
# Project created by QtCreator 2013-07-10T23:15:00
#
#-------------------------------------------------

QT       -= gui

TARGET = Core
TEMPLATE = lib

DEFINES += CORE_LIBRARY

INCLUDEPATH += inc

SOURCES += src/Game.cpp\
			src/Gameboard.cpp\
			src/Hole.cpp\
			src/AI.cpp \
			src/APlayer.cpp \
			src/Player.cpp \
			src/EasyAI.cpp \
			src/HardAI.cpp

HEADERS += inc/Game.hpp\
			inc/Gameboard.hpp\
			inc/Hole.hpp\
			inc/AI.hpp \
			inc/APlayer.hpp \
			inc/Player.hpp \
			inc/EasyAI.hpp \
			inc/HardAI.hpp

