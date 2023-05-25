
// parallel breadth - first search(BFS) implemented in C++ using the OpenMP library.
// This code takes advantage of multiple threads to explore the graph in parallel,
// improving performance.

#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>

using namespace std;

// Structure to represent a graph
struct Graph
{
    int vertices;
    vector<vector<int>> adjList;
};

// Function to add an edge to the graph
void addEdge(Graph &graph, int src, int dest)
{
    graph.adjList[src].push_back(dest);
}

// Parallel BFS function
void parallelBFS(const Graph &graph, int startVertex, vector<bool> &visited)
{
    queue<int> q;
    visited[startVertex] = true;
    q.push(startVertex);

    while (!q.empty())
    {
        int currentVertex = q.front();
        q.pop();

#pragma omp parallel for
        for (int i = 0; i < graph.adjList[currentVertex].size(); ++i)
        {
            int neighbor = graph.adjList[currentVertex][i];

#pragma omp critical
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }
}

// Driver program to test the parallel BFS
int main()
{
    int numVertices = 7;
    Graph graph;
    graph.vertices = numVertices;
    graph.adjList.resize(numVertices);

    // Add edges to the graph
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 2, 6);

    vector<bool> visited(numVertices, false);

    parallelBFS(graph, 0, visited);

    // Print the visited array
    cout << "Visited array: ";
    for (int i = 0; i < numVertices; ++i)
    {
        cout << visited[i] << " ";
    }
    cout << endl;

    return 0;
}

// Explanation:

// 1. The code starts by defining a Graph structure to represent the graph, with the number of vertices and an adjacency list to store the edges.

// 2. The `addEdge` function is used to add edges to the graph by appending the destination vertex to the adjacency list of the source vertex.

// 3. The `parallelBFS` function performs the parallel BFS traversal. It takes the graph, the starting vertex, and a reference to the `visited` array as input.

// 4. Inside the `parallelBFS` function, a queue `q` is used to store the vertices to be visited. The starting vertex is marked as visited and enqueued.

// 5. The while loop continues until the queue is empty. In each iteration, a vertex is dequeued from the front of the queue.

// 6. The `#pragma omp parallel for` directive parallelizes the loop that iterates over the neighbors of the current vertex. It distributes the iterations among the available threads to process them in parallel.

// 7. The `#pragma omp critical` directive ensures that only one thread can modify the shared data (the visited array and the queue) at a time, avoiding race conditions.

// 8. Inside the parallel loop, each neighbor is checked if it has been visited. If it hasn't, it is marked as visited, and enqueued into the queue for further exploration.

// 9. The main function sets up a test graph and calls the `parallelBFS` function with the starting vertex and the `visited`

// Run
// g++ -o ParallelBFS ParallelBFS.cpp -fopenmp
// ./ParallelBFS

// O/P:
// Visited array: 1 1 1 1 1 1 1
