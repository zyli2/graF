# Github Organization

# graF
Stores the graph drawing image produced by using the drawing functions
The graph drawing output is named output.png here

# data
Location of all the data used for producing a graph

# entry
main.cpp is here

# src
Location of all of our written code

# final-deliverables
Location of our written report, presentation powerpoint, presentation link

# tests
Stores our test cases, data test cases uses, and images produced using the test case data

# Running Instructions

Makefile

Make sure you're in the graF directory first and have your docker opened

1) mkdir build

2) cd build

3) cmake ..

Running the code

If you want to run our program with your dataset, make sure your dataset is in a csv format and it is similar to our data_subreddit_title.csv file which is in our data directory. The first value should be the source vertex and the second value should be the target vertex (the destination your source vertex reaches).

Make sure you're in the build directory and follow the steps below

1) make

2) ./main

3) follow the rest of the steps in your terminal. Our program will guide you

Test cases

Make sure you're in the build directory and follow the steps below

1) make test

2) ./test

BFS Test - looks at the accuracy for producing the shortest path for two vertices by evaluating the actual path and path length

Betweenness Centrality test - looks at whether or not our function returns the expected betweenness centrality we calculated by hand

Degree Centrality test - looks at whether or not our function returns the expected betweenness centrality we calculated by hand

Graph drawing test - idk

Data parsing test - checks if the correct amount of vertices exist and if there are a correct amount of
edges and correct edges