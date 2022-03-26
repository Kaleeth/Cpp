# CXX=g++-10
CXXFLAGS=-std=c++20 -Wall -pedantic

SRC := $(wildcard *.cpp)
OBJ := $(SRC:%.cpp=%.o)

linkage: $(OBJ)
	$(CXX) $^
	# Use `make nix-clean` on Linux
	# Use `make win-clean` on Windows

# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: nix-clean win-clean

nix-clean: $(wildcard *.o *.out)
	rm -f $^

win-clean: $(wildcard *.o *.exe)
	del $^