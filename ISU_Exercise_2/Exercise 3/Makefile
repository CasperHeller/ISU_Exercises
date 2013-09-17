EXECUTABLE=parts
CXX=g++

all : main.o part1.o part2.o
	${CXX} -o ${EXECUTABLE} main.o part1.o part2.o
	
main.o : main.cpp
	${CXX} -c main.cpp
	
part1.o : part1.cpp part1.h
	${CXX} -c part1.cpp

part2.o : part2.cpp part1.h
	${CXX} -c part2.cpp
	
clean :
	@rm -rf *o ${EXECUTABLE}
	
help :
	@echo all clean help main.o part1.o part2.o