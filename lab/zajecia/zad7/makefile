.PHONY: all
all: gen dyn brut

gen: gen.cpp
	g++ -Wall -Wextra -O2 -std=c++20 -o gen gen.cpp

dyn: dyn.cpp
	g++ -Wall -Wextra -O2 -std=c++20 -o dyn dyn.cpp

brut: brut.cpp
	g++ -Wall -Wextra -O2 -std=c++20 -o brut brut.cpp

clean:
	rm -rf *.o
	rm -rf brut dyn gen
