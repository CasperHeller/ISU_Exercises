CXX=g++
SOURCES=threads.cpp
DIR=objects/
LIBRARIES=-pthread
OBJECTS=$(SOURCES:%.cpp=$(DIR)%.o)
EXECUTABLE=threads

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LIBRARIES)

$(DIR)%.o: %.cpp $(DIR)
	$(CXX) -c $< -o $@

$(DIR):
	@mkdir $(DIR)
	
clean : 
	@rm $(OBJECTS) ${EXECUTABLE}

help :
	@echo all clean help $(EXECUTABLE) $(OBJECTS)