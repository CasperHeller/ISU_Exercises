EXECUTABLE=hello
CXX=g++

all: hello.o
	${CXX} -o ${EXECUTABLE} hello.o

hello.o: hello.cpp
	${CXX} -c hello.cpp
	
clean:
	@rm -rf *o ${EXECUTABLE}
	
help:
	@echo all hello.o clean help