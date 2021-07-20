CXX = clang++
CXXFLAGS  = -g -Wall -O3 -fopenmp=libomp
LDFLAGS = -lm 

ifdef OS
   RM = del /Q
else
   ifeq ($(shell uname), Linux)
      RM = rm
   endif
endif

.PHONY : clean

default: main

Magic.o : Magic.h Magic.cpp
	$(CXX) $(CXXFLAGS) -c Magic.cpp

Mario.o : Mario.h Mario.cpp
	$(CXX) $(CXXFLAGS) -c Mario.cpp

Platform.o : Platform.h Platform.cpp
	$(CXX) $(CXXFLAGS) -c Platform.cpp

Surface.o : Surface.h Surface.cpp
	$(CXX) $(CXXFLAGS) -c Surface.cpp

Trig.o : Trig.h Trig.cpp
	$(CXX) $(CXXFLAGS) -c Trig.cpp
	
vmath.o : vmath.h vmath.cpp
	$(CXX) $(CXXFLAGS) -c vmath.cpp

main.o: main.cpp Mario.h Magic.h Platform.h
	$(CXX) $(CXXFLAGS) -c main.cpp

main: Magic.o Mario.o Platform.o Surface.o Trig.o vmath.o main.o
	$(CXX) $(CXXFLAGS) -o main Magic.o Mario.o Platform.o Surface.o Trig.o vmath.o main.o  $(LDFLAGS)
clean:
	$(RM) *.o main



