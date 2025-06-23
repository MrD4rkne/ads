.PHONY: all
all: gen dom brut

gen: gen.cpp
	g++ -Wall -Wextra -O2 -std=c++20 -o gen gen.cpp

dom: dom.cpp
	g++ -Wall -Wextra -O2 -std=c++20 -o dom dom.cpp

brut: brut.cpp
	g++ -Wall -Wextra -O2 -std=c++20 -o brut brut.cpp

clean:
	rm -rf *.o
	rm -rf brut dom gen
