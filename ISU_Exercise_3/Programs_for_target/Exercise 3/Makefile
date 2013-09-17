CXX=g++
SOURCES=main.cpp part1.cpp part2.cpp
OBJDIR:=host
OBJECTS:=$(addprefix $(OBJDIR)/,$(SOURCES:.cpp=.o))
EXECUTABLE=parts

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)

$(OBJDIR)/%.o: %.c
	$(CXX) -c $< -o $@

$(OBJDIR):
	@mkdir $(OBJDIR)
	
clean : 
	@rm $(OBJECTS) ${EXECUTABLE}

help :
	@echo all clean help $(EXECUTABLE) $(OBJECTS)