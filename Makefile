all: build

build:
	g++ main.cpp bmp.cpp ascii.cpp -o ascii

clean:
	rm ascii
