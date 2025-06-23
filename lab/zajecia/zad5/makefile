.PHONY: all
all: gen kin brut

gen: gen.cpp
	g++ -Wall -Wextra -O2 -std=c++20 -o gen gen.cpp

kin: kin.cpp
	g++ -Wall -Wextra -O2 -std=c++20 -o kin kin.cpp

brut: brut.cpp
	g++ -Wall -Wextra -O2 -std=c++20 -o brut brut.cpp

clean:
	rm -rf *.o
	rm -rf brut kin gen
