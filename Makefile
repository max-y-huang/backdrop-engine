CXX = g++
CXXFLAGS = -std=c++14 -Wall -I D:/sfml/include
EXEC = game.exe
SOURCES = $(wildcard *.cc */*.cc */*/*.cc)  # TODO: make better
OBJECTS = ${SOURCES:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}

test: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -L D:/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system

prod:
	${CXX} ${OBJECTS} -o ${EXEC} -L D:/sfml/lib -mwindows -lsfml-graphics -lsfml-window -lsfml-system

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
