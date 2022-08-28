# Run the Program
1. Build the program using: "make" or "make prog1".
2. Run the program using: "./prog1 <path_to_points_file>".
3. Clean the generated files using: "make clean".

# Input File Format
The first line is the number of points. The rest of the lines are "<x_coor>, <y_coor>". There must be exactly one space after the comma.
For example, an input file might look like: <br />
4 <br />
-0.5, -0.5 <br />
-0.5, 0.5 <br />
0.5, -0.5 <br />
0.5, 0.5

# Explaining prog1.cpp
prog1.cpp implements Quickhull.
The setUp function reads in the input and draws a line from the left-most point to the right-most point. Points that are above the line are inserted into aboveLine, and points that are below the line are inserted into belowLine.
The solveAbove function recursively finds the points in aboveLine that make up the convex hull.
The solveBelow function recursively finds the points in belowLine that make up the convex hull.
The sortAndRemoveCollinearAndPrint function sorts the points in counterclockwise order, remove collinear points, and output the result to standard out.

# Time Complexity
The rumtime vs size plot can be found in "Runtime vs Size.png". The x-axis is the number of points and the y-axis is the runtime in microsecond. Note that I only included setUp, solveAbove, and solveBelow when measuring the runtime. The reason is that sortAndRemoveColinearAndPrint is not about Quickhull.
From the plot, we verify that Quickhull runs in linearithmic O(nlogn) time complexity in average cases. Although Quickhull runs in O(n^2) time complexity in the worst case, it is almost impossible to happen in practice.
