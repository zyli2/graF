Leading Questions: 

What is the shortest path from one subreddit to another using hyperlinks from the subreddit posts? What subreddit has the most influence on the flow of information on Reddit?
Our group wants to create a general analysis tool that can find the shortest path from one subreddit to another. We’ve chosen to perform this analysis on a subreddit dataset, originated from the Stanford Network Analysis Project webpage, that provides information about all the subreddit hyperlinks posted within a subreddit. We could store the dataset in a directed graph where a node will represent a subreddit and an edge will represent whether or not there exists a hyperlink to another subreddit. We will denote the connection (edge) between two subreddits by a value of 1 and otherwise. A value of 1 means that there exists a hyperlink from the source subreddit to the target subreddit. Other values mean that there isn’t such a connection.To find the shortest path, we’ve decided on using BFS since our weights are designed to be 1.

“Influence on the flow of information” is essentially asking what subreddit is visited the most between paths of one subreddit to another. To find that subreddit, we need to calculate the betweenness centrality of every node using the expression below. 

The bottom of the fraction is the total number of shortest paths from node s to node t which can be calculated using BFS modified to find all paths instead of one shortest path. The top of the fraction is the number of those paths that pass through v but only when v isn’t an end point. We will compare every node’s betweenness centrality and select the node with the centrality closest to one as the best node (subreddit).

We will also be computing a drawing of our graph as an additional analysis on Reddit’s subreddit network using the Force-directed Graph Drawing or Layout Algorithm.
 
Dataset Acquisition: 

Data format:
Our dataset is derived from the link below: http://snap.stanford.edu/data/ http://snap.stanford.edu/data/soc-RedditHyperlinks.html
And after deleting some irrelevant data from the original file, we extract the two variables (source and target) from the Reddit Hyperlinks-Title and store them in a csv file (~12mb). It’s in our git repository.
The value of the data will be a text (string). 

Data Correction: 
Since our data is given in the tsv format, we are first going to use MS Excel to get rid of unwanted properties so that our file is lighter. We strip the data until we just have the source subreddit and the destination subreddit. We will then convert this to a csv file which will make data processing easier. 
We also discover that there is a lot of repeated data from the file which can cause some potential problems when parsing data. Therefore, we decided to create two copies of the dataset – one of them contains no repeated data and the other one will contain the repeated data(this one could be used for future applications like the strength of the edge[number of repetition]).
We might have multiple connected components generated from our data. Though this is acceptable for Dijikstra’s algorithm, we may need to deal with this differently when exploring betweenness.

Data Storage:
The data structure will be a source node with an adjacency matrix that contains all the target nodes from the given source. 
Data storage O(n^2)


Algorithms:

We will be using BFS to find the shortest path between two given subreddits. We will construct a graph given by the csv file by parsing this data with an available library. When constructing the graph, we will store each subreddit to a node and every target of the source into an adjacency list. Moreover, we will be using BFS for traversing the graph, and counting the number of connected components in the graph. 

1. BFS:

	Function Inputs:
	
No input since we can start with an arbitrary node of the graph.

Function Outputs:

Return the number of connected components of the graph. 

Function Efficiency:

The expected runtime for BFS will be O(n), in which n is the number of nodes. 

2. Betweenness Centrality

	Function Inputs:
	
No input since we’re calculating every node’s betweenness centrality

Function Outputs:

Returns the node with the betweenness centrality closest to 1

Function Efficiency:

The expected runtime is O(n) as we’re utilizing BFS to implement this function

3. Graph Visualization (Force-directed Graph Drawing or Layout Algorithm):

	Function Inputs: 
	
	The graph, possibly by each node.

	Function Outputs: 
	
	A visual representation of the graph. 
	
	Efficiency: 
	
	The expected runtime will be O(n^3) for Force-directed Graph and O(nm) for Layout Algorithm, where n is the number of nodes of the graph and m is the number of edges of the graph. 


Timeline:

In the first week, finish cleaning up the data in the way we want and come up with an appropriate data structure to store the data. 

In the second week, identify all functions needed for this project, and complete easier functions with testing (e.g. insertVertex, insertEdge, areAdjacent). Finish BFS with adequate testing. 

In the third week, finish another core algorithm - such as calculating betweenness centrality - and ensure the functionality of the algorithm. If we finish the betweenness centrality function early, we’ll proceed to implementing force-directed graph drawing algorithms

– Thanksgiving Break - 

In the last week, complete the rest of the functions and wrap up the project with final testing of the program as a whole. Clean up the codes and complete the documentation (if still incomplete). Create the presentation and record the videos to show the final results. 


Future Ideas:

We are thinking about incorporating a measure of connection strength graph. This will be especially useful in describing each edge as it relates to another. Another idea we would want to explore is creating a visual for our graph. It would be interesting to visually see what subreddit has the most hyperlinks to other subreddits. A graphic output could also help with looking at our analyses from a different perspective, which may improve our understanding on our chosen dataset. To accomplish this, we will choose between the layered algorithm and Force-directed graph drawing algorithms.
