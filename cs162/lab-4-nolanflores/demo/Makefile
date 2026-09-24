CXX = g++
CXXFLAGS = -g
EXE = run

$(EXE): main.o person.o
	$(CXX) $(CXXFLAGS) main.o person.o -o $(EXE)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

person.o: person.cpp person.hpp
	$(CXX) $(CXXFLAGS) -c person.cpp

clean:
	rm -rf *.o $(EXE)
