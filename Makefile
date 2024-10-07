CXX = g++
CXXFLAGS = -I include -Wall -std=c++11

# Specify the source files and the corresponding object files
SOURCES = src/main.cpp src/parser.cpp src/scanner.cpp src/codegen.cpp src/symbolTable1.cpp src/reporting.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Define the target executable
TARGET = compiler.exe

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile each .cpp file to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the build
clean:
	rm -f $(OBJECTS) $(TARGET)
