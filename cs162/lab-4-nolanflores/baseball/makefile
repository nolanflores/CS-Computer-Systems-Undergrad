CXX = g++
CXXFLAGS = -g
EXE = run

$(EXE): main.o baseball_player.o
	$(CXX) $(CXXFLAGS) main.o baseball_player.o -o $(EXE)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

baseball_player.o: baseball_player.cpp
	$(CXX) $(CXXFLAGS) -c baseball_player.cpp

clean:
	rm -rf *.o $(EXE)
