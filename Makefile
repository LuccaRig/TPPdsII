CXX = g++
CXXFLAGS = -g -Wall -O3 -std=c++11
INC_DIRS = -I include/
LIB_DIRS = -L/usr/lib/x86_64-linux-gnu/
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR = src
OBJDIR = build
INCLUDEDIR = include
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

EXECUTABLE = Game.app

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIB_DIRS) $^ -o $@ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INC_DIRS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	-rm -rf $(OBJDIR) $(EXECUTABLE)