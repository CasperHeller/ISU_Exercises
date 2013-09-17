CC=g++
SOURCES=main.cpp part1.cpp part2.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=parts

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

%.o: %.c
	$(CC) -c $< -o $@

clean : 
	@rm -rf *o ${EXECUTABLE}

help :
	@echo all clean help $(EXECUTABLE) $(OBJECTS)