CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -ggdb3
EXEC = chess
OBJECTS = chessboard.o subject.o observer.o chess.o textdisplay.o stat.o exception.o main.o history.o graphic.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
