CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

OpenGLTest: main.cpp
	g++ $(CFLAGS) -o ./bin/test *.cpp include/*.cpp glad/src/glad.c $(LDFLAGS)

.PHONY: test clean

test: test
	./test

clean:
	rm -f test
