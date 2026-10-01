CFLAGS = -std=c++17 -O2

compile:
	g++ $(CFLAGS) -o ./bin/program *.cpp `sdl2-config --cflags --libs`

run:
	./bin/program

clean:
	rm -f ./bin/*
