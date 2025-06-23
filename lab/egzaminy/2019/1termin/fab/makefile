CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -O2 -g

SOURCES = $(wildcard *.cpp)
TARGETS = $(SOURCES:.cpp=)

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)