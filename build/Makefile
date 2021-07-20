CXX = clang++
CXXFLAGS  = -g -Wall -O3 -fopenmp=libomp -march=native
LDFLAGS = -lm

.PHONY : clean

default: main

Magic.o : ../Magic.h ../Magic.cpp
	$(CXX) $(CXXFLAGS) -c ../Magic.cpp -o Magic.o

Mario.o : ../Mario.h ../Mario.cpp
	$(CXX) $(CXXFLAGS) -c ../Mario.cpp -o Mario.o

Platform.o : ../Platform.h ../Platform.cpp
	$(CXX) $(CXXFLAGS) -c ../Platform.cpp -o Platform.o

Surface.o : ../Surface.h ../Surface.cpp
	$(CXX) $(CXXFLAGS) -c ../Surface.cpp -o Surface.o

Trig.o : ../Trig.h ../Trig.cpp
	$(CXX) $(CXXFLAGS) -c ../Trig.cpp -o Trig.o
	
vmath.o : ../vmath.h ../vmath.cpp
	$(CXX) $(CXXFLAGS) -c ../vmath.cpp -o vmath.o

main.o: ../main.cpp ../Mario.h ../Magic.h ../Platform.h
	$(CXX) $(CXXFLAGS) -c ../main.cpp -o main.o

main: Magic.o Mario.o Platform.o Surface.o Trig.o vmath.o main.o
	$(CXX) $(CXXFLAGS) -o main Magic.o Mario.o Platform.o Surface.o Trig.o vmath.o main.o  $(LDFLAGS)
	
# Utility targets
clean:
	rm *.o main

# To run do `make args="foo bar" run`
# make doesn't provide a nicer way to pass args
run:
	main $(args)