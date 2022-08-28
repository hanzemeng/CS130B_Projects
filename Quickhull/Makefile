prog1: prog1.o Line.o
	g++ prog1.o Line.o -std=c++17 -Wall -o prog1

prog1.o: prog1.cpp Line.h
	g++ prog1.cpp -std=c++17 -Wall -c

Line.o: Line.cpp Line.h
	g++ Line.cpp -std=c++17 -Wall -c

clean:
	rm -f *.o prog1

runTime:
	./prog1 points_10.txt
	./prog1 points_20.txt
	./prog1 points_30.txt
	./prog1 points_40.txt
	./prog1 points_50.txt
	./prog1 points_100.txt
	./prog1 points_500.txt
	./prog1 points_1000.txt
	./prog1 points_5000.txt
	./prog1 points_10000.txt
	./prog1 points_50000.txt
	./prog1 points_100000.txt
	./prog1 points_500000.txt
	./prog1 points_1000000.txt
