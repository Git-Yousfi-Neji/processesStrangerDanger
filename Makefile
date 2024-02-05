CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -O2
INCLUDES := -I/include/ -I/usr/include/libxml2/ -I/config/

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp, obj/%.o, $(SRCS))
TARGET := bin/processesStrangerDanger
DEPS := $(OBJS:.o=.d)

# Add the XML parsing source file to the list of source files
XML_SRC := src/xml_parser.c
XML_OBJ := obj/xml_parser.o

# Rule to build the executable
$(TARGET): $(OBJS) $(XML_OBJ)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ -lxml2

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
run: $(TARGET)
	./$(TARGET)

# Watch for changes and trigger a rebuild
.PHONY: watch
watch:
	while true; do \
	    inotifywait -r -e modify -e create -e delete -e move src include data python_scripts scripts; make;\
	done &
