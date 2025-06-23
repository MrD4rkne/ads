CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -O2 -g

SOURCES = $(wildcard *.cpp)
TARGETS = $(SOURCES:.cpp=.a)

all: $(TARGETS)

%.a: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
	chmod +x $@

clean:
	rm -f $(TARGETS)