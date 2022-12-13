
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
Location of our written report, presentation powerpoint and presentation link

# tests
Stores our test cases, data test cases uses, and images produced using the test case data

# Running Instructions

BUILDING THE CODE:

Make sure you're in the graF directory first and have your docker opened

1) ```mkdir build```

2) ```cd build```

3) ```cmake ..```

RUNNING THE CODE:

CAUTION: If you want to run our program with your dataset, make sure your dataset is in a csv format similar to our data_subreddit_title.csv file. The first value should be the source vertex and the second value should be the target vertex (the destination your source vertex reaches). Remember to also place your csv file in the data directory or else the program will not work with your dataset.

Make sure you're in the build directory and follow the steps below

1) ```make```

2) ```./main```

3) follow the rest of the steps in your terminal. Our program will guide you

RUNNING THE TEST CASES:

Make sure you're in the build directory and follow the steps below

1) ```make test```

2) ```./test```

TEST CASE DESCRIPTIONS

BFS Test - looks at the accuracy for producing the shortest path for two vertices by evaluating the actual path and path length.

Betweenness Centrality test - looks at whether or not our function returns the expected betweenness centrality we calculated by hand.

Graph drawing test - the drawing output will be manually inspected to ensure it has the right number of edges and nodes.

Other functions - test whether each function has the intended functionality.