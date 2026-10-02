CFLAGS = -std=c++17 -O2
LDFLAGS = -lX11

compile:
	g++ $(CFLAGS) -o ./bin/program *.cpp ./include/*.cpp $(LDFLAGS) `sdl2-config --cflags --libs`

run:
	./bin/program

clean:
	rm -f ./bin/*
