CXXFLAGS = -Wall -g -Iinclude
CXX=g++

src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)

Saboteur: $(obj)
	$(CXX) -o $@ $^

.PHONY: clean

clean:
	rm -f src/*.o
