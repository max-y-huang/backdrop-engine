CXX = g++
CXXFLAGS = -std=c++14 -Wall -I D:/sfml/include
SOURCES = $(wildcard *.cc */*.cc */*/*.cc)  # TODO: make better
OBJECTS = ${SOURCES:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}

dev: ${OBJECTS}
	${CXX} ${OBJECTS} -o dev.exe -L D:/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system

prod:
	${CXX} ${OBJECTS} -o game.exe -L D:/sfml/lib -mwindows -lsfml-graphics -lsfml-window -lsfml-system

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} game.exe test.exe
