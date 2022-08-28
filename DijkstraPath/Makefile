FLAGS = -std=c++17 -Wall

prog2: prog2.o Vertex.o
	g++ ${FLAGS} prog2.o Vertex.o -o prog2

prog2.o: prog2.cpp Vertex.h
	g++ ${FLAGS} prog2.cpp -c

Vertex.o: Vertex.cpp Vertex.h
	g++ ${FLAGS} Vertex.cpp -c


clean:
	rm -f *.o prog2 out.txt

run:
	./prog2 test/input_500_2.txt out.txt