# DijkstraPath

## Run the Program
1. Build the project by typing: make or make prog2
2. Run the project by typing: ./prog2 <input_file_path> <output_file_path>
3. Clean the project by typing: make clean
4. I recommend naming the output file to be out.txt. This allows the output file to be cleaned up by the make clean command.

## Input File Format
The first line is the number of vertices. Each line after is each vertex's x coordinate, a space, and the vertex's y coordinate. After the vertices, there is another line representing the number of edges. If this number is 0, then the graph is complete. Else, the rest of lines are vertex1, a space, and vertex2; implying there is an undirected edge between vertex1 and vertex2. For example, a possible input file looks like: <br />
4<br />
-3.44 8.91<br />
7 3<br />
56.12 -33<br />
12 32<br />
4<br />
0 2<br />
1 3<br />
2 3<br />
1 0<br />

## Program Design
This program uses a set (a balanced search tree) to implement Dijkstra's shortest path algorithm. Find the minimum in the set costs O(log(n)); update a value in the set costs O(log(n)). Finding the minimum happens for v times; updating the value happens for at most e times. So the time complexity for Dijkstra's shortest path is: O(vlog(v) + elog(v))
