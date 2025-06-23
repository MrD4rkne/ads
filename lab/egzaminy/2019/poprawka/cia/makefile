CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -O2 -g

SOURCES = $(wildcard *.cpp)
TARGETS = $(SOURCES:.cpp=.a)

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@.a $<

clean:
	rm -f $(TARGETS)