CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic
INCLUDES := -I include -I/usr/include/libxml2/
LIBS := -lxml2
SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp, obj/%.o, $(SRCS))
EXECUTABLE := bin/processesStrangerDanger
DEPS := $(OBJS:.o=.d)

# Add the XML parsing source file to the list of source files
XML_SRC := src/xml_parser.c
XML_OBJ := obj/xml_parser.o

# Rule to build the executable
$(EXECUTABLE): $(OBJS) $(XML_OBJ)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

# Rule to build object files from source files
obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -c $< -o $@

# Rule to build object files from XML parsing source file
obj/xml_parser.o: $(XML_SRC)
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -c $< -o $@

# Include dependency files
-include $(DEPS)

# Phony target to clean the project
.PHONY: clean
clean:
	rm -rf bin obj

# Phony target to run the executable
.PHONY: run
run: $(EXECUTABLE)
	./$(EXECUTABLE)
