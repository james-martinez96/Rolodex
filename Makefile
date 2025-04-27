# Makefile for Rolodex

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17

# Output file
TARGET = Rolodex

# Source files
SRCS = rolodex.cpp

# The main build rule
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Clean up build files
clean:
	rm -f $(TARGET)
