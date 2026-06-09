CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++17 \
	` sdl2-config --cflags ` \
	-Iinclude

LDFLAGS = \
	` sdl2-config --libs ` \
	-lSDL2_ttf

SRC = \
	src/main.cpp

OUT = bin/memo-pad-cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)
