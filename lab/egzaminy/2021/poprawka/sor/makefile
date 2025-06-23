CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -O2 -g

all: brut gen sor

brut: brut.cpp
	$(CXX) $(CXXFLAGS) -o brut brut.cpp

gen: gen.cpp
	$(CXX) $(CXXFLAGS) -o gen gen.cpp

sor: sor.cpp
	$(CXX) $(CXXFLAGS) -o sor sor.cpp

clean:
	rm -f brut gen sor