CXX = g++
CXXFLAGS = -g -Wall -O3 -std=c++20
INC_DIRS = -I include/ -I third_party/
LIB_DIRS = -L/usr/lib/x86_64-linux-gnu/
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

OBJS = build/Game.o build/main.o

main: $(OBJS)
	$(CXX) $(OBJS) -o Game.app $(LIB_DIRS) $(LIBS)

build/Game.o: src/Game.cpp
	$(CXX) $(CXXFLAGS) $(INC_DIRS) -c -o $@ $<

build/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) $(INC_DIRS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJS) Game.app