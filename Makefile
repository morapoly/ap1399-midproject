CXX = g++
CXXFLAGS = -std=c++2a -Wall -c
LXXFLAGS = -std=c++2a -Ih -pthread
OBJECTS = ./obj/main.o ./obj/mid_project.o ./obj/number_puzzle.o
TARGET = main

$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS)
./obj/number_puzzle.o: ./cpp/number_puzzle.cpp
	$(CXX) $(CXXFLAGS) ./cpp/number_puzzle.cpp -o ./obj/number_puzzle.o
./obj/mid_project.o: ./cpp/mid_project.cpp
	$(CXX) $(CXXFLAGS) ./cpp/mid_project.cpp -o ./obj/mid_project.o
./obj/main.o: ./cpp/main.cpp ./h/mid_project.h
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
clean:
	rm -fv $(TARGET) $(OBJECTS)