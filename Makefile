CXX = g++
CXXFLAGS = -std=c++14 -Wall
EXEC = main.out
SOURCES = main.cc $(shell find ./engine -name '*.cc')
OBJECTS = ${SOURCES:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}

main: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lsfml-graphics -lsfml-window -lsfml-system

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
