SOURCES=main.cpp part1.cpp
EXE=parts
CXXFLAGS=-Wall
CXX=g++
# Directories containing header files other than /usr/include (-Idir):
INCLUDES = -I.
# Library paths in addition to /usr/lib (-Ldir):
LFLAGS = -L./lib
# Libraries to link into executable (-lname):
LIBS =  -lpart2
OBJECTS=$(SOURCES:.cpp=.o)
DEPS=$(SOURCES:.cpp=.d)

$(EXE): $(DEPS) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(OBJECTS) $(LFLAGS) $(LIBS)

%.d: %.cpp
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $^ > $@

clean: 
	@rm $(OBJECTS) ${EXE} $(DEPS)

-include $(DEPS)