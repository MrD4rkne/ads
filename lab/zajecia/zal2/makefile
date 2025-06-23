.PHONY: all
all: gen ogr brut

gen: gen.cpp
	g++ -Wall -Wextra -O2 -std=c++20 -o gen gen.cpp

ogr: ogr.cpp
	g++ -Wall -Wextra -O2 -std=c++20 -o ogr ogr.cpp

brut: brut.cpp
	g++ -Wall -Wextra -O2 -std=c++20 -o brut brut.cpp

clean:
	rm -rf *.o
	rm -rf brut dom gen
