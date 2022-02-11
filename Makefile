CXX = g++
CXXFLAGS = -std=c++14 -Wall -I D:/sfml/include
SOURCES = $(wildcard *.cc */*.cc */*/*.cc)  # TODO: make better
OBJECTS = ${SOURCES:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}

dev: ${OBJECTS}
	${CXX} ${OBJECTS} -o dev.exe -L D:/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system

prod:
	windres icon.rc icon.o
	${CXX} icon.o ${OBJECTS} -o game.exe -L D:/sfml/lib -mwindows -lsfml-graphics -lsfml-window -lsfml-system

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} main.o icon.o game.exe dev.exe
