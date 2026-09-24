CXX = g++
CXXFLAGS = -g
EXE = run

$(EXE): run_catalog.o catalog.o
	$(CXX) $(CXXFLAGS) run_catalog.o catalog.o -o $(EXE)

run_catalog.o: run_catalog.cpp
	$(CXX) $(CXXFLAGS) -c run_catalog.cpp

catalog.o: catalog.cpp
	$(CXX) $(CXXFLAGS) -c catalog.cpp

clean:
	rm -rf *.o $(EXE)
