CXX=g++
SOURCES=hello.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=hello

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(OBJECTS) -o $@

%.o: %.c
	$(CXX) -c $< -o $@

clean : 
	@rm -rf *o ${EXECUTABLE}

help :
	@echo all clean help $(EXECUTABLE) $(OBJECTS)