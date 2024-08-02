# Define the compiler to use
CXX = g++

# Define compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# Define directories
MAINDIR = main
SRCDIR = src
INCLUDEDIR = include
BUILDDIR = build
BINDIR = bin

# Define the target executable
TARGET = $(BINDIR)/hanoi

# Find all source files
MAIN_SRCS = $(wildcard $(MAINDIR)/*.cpp)
SRC_SRCS = $(wildcard $(SRCDIR)/*.cpp)
SRCS = $(MAIN_SRCS) $(SRC_SRCS)

# Generate object files from source files
MAIN_OBJS = $(patsubst $(MAINDIR)/%.cpp, $(BUILDDIR)/%.o, $(MAIN_SRCS))
SRC_OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRC_SRCS))
OBJS = $(MAIN_OBJS) $(SRC_OBJS)

# Default rule
all: $(TARGET)

# Rule to link the target executable
$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $(OBJS) -o $(TARGET)

# Rule to compile main source files into object files
$(BUILDDIR)/%.o: $(MAINDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile other source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the build directory
clean:
	rm -rf $(BUILDDIR) $(BINDIR)

# Phony targets
.PHONY: all clean