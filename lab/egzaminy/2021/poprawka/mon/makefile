CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -O2 -g

all: brut gen mon

brut: brut.cpp
	$(CXX) $(CXXFLAGS) -o brut brut.cpp

gen: gen.cpp
	$(CXX) $(CXXFLAGS) -o gen gen.cpp

mon: mon.cpp
	$(CXX) $(CXXFLAGS) -o mon mon.cpp

clean:
	rm -f brut gen mon