prog4: prog4.o Point.o
	g++ -std=c++17 prog4.o Point.o -o prog4

prog4.o: prog4.cpp Point.h
	g++ -c -std=c++17 prog4.cpp

Point.o: Point.cpp Point.h
	g++ -c -std=c++17 Point.cpp

clean:
	rm -f *.o prog4

run:
	./prog4 test/input_2.txt