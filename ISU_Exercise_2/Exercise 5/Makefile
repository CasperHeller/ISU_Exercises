SOURCES=time.cpp
EXE=time
CXXFLAGS=-Wall
CXX=g++
# Directories containing header files other than /usr/include (-Idir):
INCLUDES = 
# Library paths in addition to /usr/lib (-Ldir):
LFLAGS = 
# Libraries to link into executable (-lname):
LIBS =  -lrt
OBJECTS=$(SOURCES:.cpp=.o)
DEPS=$(SOURCES:.cpp=.d)

$(EXE): $(DEPS) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(OBJECTS) $(LFLAGS) $(LIBS)

%.d: %.cpp
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $^ > $@

clean: 
	@rm $(OBJECTS) ${EXE} $(DEPS)

-include $(DEPS)