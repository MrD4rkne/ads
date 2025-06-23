.PHONY: all
all: gen mal brut

gen: gen.cpp
	g++ -Wall -Wextra -O2 -std=c++20 -o gen gen.cpp

mal: mal.cpp
	g++ -Wall -Wextra -O2 -std=c++20 -o mal mal.cpp

brut: brut.cpp
	g++ -Wall -Wextra -O2 -std=c++20 -o brut brut.cpp

clean:
	rm -rf *.o
	rm -rf brut mal gen
