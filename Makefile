CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla
EXEC = chess
OBJECTS = main.o board.o textdisplay.o graphicsdisplay.o square.o window.o
DEPENDS = ${OBJECTS:.o=.d}
FLAG = -lX11

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${FLAG}

-include ${DEPENDS}

.PHONY:
	clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
