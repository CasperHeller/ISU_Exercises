SOURCES=main.cpp part1.cpp part2.cpp
EXECUTABLE=parts
LIBRARIES=-pthread
CFLAGS=-Wall
###
ifneq ($(ARCH),target)
CXX=g++
DIR=host/
EXE=$(EXECUTABLE)
else
CXX=arm-angstrom-linux-gnueabi-g++
DIR=target/
EXE=$(addsuffix .target,$(EXECUTABLE))
endif

OBJECTS=$(SOURCES:%.cpp=$(DIR)%.o)

$(EXE): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LIBRARIES) $(DEBUG)
	
$(DIR)%.o: %.cpp $(DIR)
	$(CXX) $(CFLAGS) -c $< -o $@ 
	
$(DIR):
	@mkdir $(DIR)
	
clean: 
	@rm $(OBJECTS) $(EXE)
	@rmdir $(DIR)
	
help:
	@echo "Instructions for makefile:"
	@echo "make [OPTIONS]                 make for host"
	@echo "make ARCH=target [OPTIONS]     make for target"
	@echo "OPTIONS:"
	@echo "clean          removes objects directory and executable"