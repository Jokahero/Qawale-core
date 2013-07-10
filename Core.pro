#-------------------------------------------------
#
# Project created by QtCreator 2013-07-10T23:15:00
#
#-------------------------------------------------

QT       -= gui

TARGET = Core
TEMPLATE = lib

DEFINES += CORE_LIBRARY

SOURCES += Gameboard.cpp\
			Hole.cpp\
			IA.cpp\
			Player.cpp

HEADERS += Gameboard.hpp\
			Hole.hpp\
			IA.hpp\
			Player.hpp\


unix:!symbian {
	maemo5 {
		target.path = /opt/usr/lib
	} else {
		target.path = /usr/lib
	}
	INSTALLS += target
}
