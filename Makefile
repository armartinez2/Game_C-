all: bike

bike: main.cpp
	g++ main.cpp -w -lSDL2 -lSDL2_image -o Sheeba -std=c++11
clean:
	rm Sheeba
