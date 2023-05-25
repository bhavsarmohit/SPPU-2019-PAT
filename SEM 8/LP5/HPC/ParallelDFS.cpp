
// parallel depth-first search (DFS) implemented in C++ using the OpenMP library.
// This code explores the graph in parallel using multiple threads.

#include <iostream>
#include <vector>
#include <stack>
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

// Parallel DFS function
void parallelDFS(const Graph &graph, int startVertex, vector<bool> &visited)
{
    stack<int> stk;
    stk.push(startVertex);

    while (!stk.empty())
    {
        int currentVertex = stk.top();
        stk.pop();

        if (!visited[currentVertex])
        {
#pragma omp critical
            {
                if (!visited[currentVertex])
                {
                    visited[currentVertex] = true;
                    cout << "Visited vertex: " << currentVertex << endl;
                }
            }

#pragma omp parallel for
            for (int i = 0; i < graph.adjList[currentVertex].size(); ++i)
            {
                int neighbor = graph.adjList[currentVertex][i];
                stk.push(neighbor);
            }
        }
    }
}

// Driver program to test the parallel DFS
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

    parallelDFS(graph, 0, visited);

    return 0;
}

// Explanation:

// 1. The code begins by defining a Graph structure to represent the graph, with the number of vertices and an adjacency list to store the edges.

// 2. The addEdge function is used to add edges to the graph by appending the destination vertex to the adjacency list of the source vertex.

// 3. The parallelDFS function performs the parallel DFS traversal. It takes the graph, the starting vertex, and a reference to the visited array as input.

// 4. Inside the parallelDFS function, a stack stk is used to store the vertices to be visited. The starting vertex is pushed onto the stack.

// 5. The while loop continues until the stack is empty. In each iteration, a vertex is popped from the top of the stack.

// 6. The #pragma omp critical directive ensures that only one thread can modify the shared data (the visited array and the stack) at a time, avoiding race conditions.

// 7. The condition if (!visited[currentVertex]) checks if the vertex has not been visited before. This prevents unnecessary multiple visits by different threads.

// 8. If the vertex has not been visited, it is marked as visited and printed.

// 9. The #pragma omp parallel for directive parallelizes the loop that iterates over the neighbors of the current vertex. It distributes the iterations among the available threads to process them in parallel.

// 10. Inside the parallel loop, each neighbor is pushed onto the stack for further exploration.

// 11. The main function sets up a test graph and calls the parallelDFS function with the starting vertex and the visited array.

// 12. The program prints the visited vertices during the DFS traversal.

// Note: The order of visited vertices may vary due to the parallel execution of threads.

// Run
// g++ -o ParallelDFS ParallelDFS.cpp -fopenmp
// ./ParallelDFS

// O/P:
// Visited vertex: 0
// Visited vertex: 2
// Visited vertex: 5
// Visited vertex: 6
// Visited vertex: 1
// Visited vertex: 3
// Visited vertex: 4
