all: proj5.exe

random.o: random.h random.cpp constants.h
	g++ -std=c++98 -g -Wall -c random.cpp -o random.o

CarClass.o: CarClass.h CarClass.cpp constants.h
	g++ -std=c++98 -g -Wall -c CarClass.cpp -o CarClass.o

EventClass.o: EventClass.h EventClass.cpp constants.h
	g++ -std=c++98 -g -Wall -c EventClass.cpp -o EventClass.o

IntersectionSimulationClass.o: IntersectionSimulationClass.h IntersectionSimulationClass.cpp constants.h random.h CarClass.h EventClass.h SortedListClass.h FIFOQueueClass.h LinkedNodeClass.h
	g++ -std=c++98 -g -Wall -c IntersectionSimulationClass.cpp -o IntersectionSimulationClass.o

proj5.o: project5.cpp random.h IntersectionSimulationClass.h constants.h 
	g++ -std=c++98 -g -Wall -c project5.cpp -o proj5.o

proj5.exe:  proj5.o random.o CarClass.o EventClass.o IntersectionSimulationClass.o
	g++ -std=c++98 -g -Wall proj5.o random.o CarClass.o EventClass.o IntersectionSimulationClass.o -o proj5.exe

clean:
	rm -f *.o *.exe