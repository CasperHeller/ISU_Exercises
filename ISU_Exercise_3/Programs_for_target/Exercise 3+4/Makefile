CXX=g++
SOURCES=main.cpp part1.cpp part2.cpp
DIR:=host/
OBJECTS:=$(SOURCES:%.cpp=$(DIR)%.o)
EXECUTABLE=parts

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) -o $(DIR)$@ $(OBJECTS)

$(DIR)%.o: %.cpp $(DIR)
	$(CXX) -c $< -o $@

$(DIR):
	@mkdir $(DIR)
	
clean : 
	@rm $(OBJECTS) $(DIR)${EXECUTABLE}
	@rmdir $(DIR)

help :
	@echo all clean help $(EXECUTABLE) $(OBJECTS)