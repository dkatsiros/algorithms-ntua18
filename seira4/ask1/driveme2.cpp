#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <limits.h>

using namespace std;

int read_int()
{
    int n = 0;
    char c = getchar_unlocked();
    while (!('0' <= c && c <= '9'))
    {
        c = getchar_unlocked();
    }
    while ('0' <= c && c <= '9')
    {
        n = n * 10 + c - '0';
        c = getchar_unlocked();
    }
    return n;
}

int V;
long int N, M, K, Q;
int u, v, p;
long int graph[1100][1100];
long int dijkstraResults[1100][1100];
int questions[10000][3];
int haveDijkstraResults[1100];

void setHaveDijkstraResults()
{
    for (int i = 0; i < 1100; i++)
    {
        haveDijkstraResults[i] = 0;
    }
}

void setDijkstraResultsZero()
{
    for (int i = 0; i < 1100; i++)
    {
        for (int j = 0; j < 1100; j++)
        {
            dijkstraResults[i][j] = INT_MAX;
        }
    }
}

void setGraphZeros()
{
    for (int i = 0; i < 1100; i++)
    {
        for (int j = 0; j < 1100; j++)
        {
            graph[i][j] = 0;
        }
    }
}

void printAnswer(long int *dist, int dest)
{
    int min = dist[dest];
    for (int i = 0; i <= p; i++)
    {
        if (dist[dest + i * N] < min)
        {
            min = dist[dest + i * N];
        }
    }
    if (min != INT_MAX)
    {
        printf("%ld\n", min);
    }
    else
    {
        printf("IMPOSSIBLE\n");
    }
}

// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(long int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int V, int src, int dest)
{
    long int dist[V]; // The output array. dist[i] will hold the shortest
        // distance from src to i

    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
        // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    for (int i = 0; i < V; i++)
    {
        dijkstraResults[src][i] = dist[i];
    }
    haveDijkstraResults[src] = 1;

    printAnswer(dist, dest);
}

int main()
{
    N = read_int();
    M = read_int();
    K = read_int();
    Q = read_int();

    setGraphZeros();
    setDijkstraResultsZero();
    setHaveDijkstraResults();
    long int dUV;

    for (int i = 0; i < M; i++)
    {
        u = read_int() - 1;
        v = read_int() - 1;
        scanf("%ld", &dUV);
        graph[u][v] = dUV;
        for (int k = 1; k <= K; k++)
        {
            graph[u + N * k][v + N * k] = dUV;
            // x,y e [1 eos v + k-Nades]
            graph[v + N * (k - 1)][u + N * k] = dUV;
        }
    }

    for (int i = 0; i < Q; i++)
    {
        u = read_int() - 1;
        v = read_int() - 1;
        p = read_int();
        questions[i][0] = u;
        questions[i][1] = v;
        questions[i][2] = p;
    }

    for (int i = 0; i < Q; i++)
    {
        int source = questions[i][0];
        int dest = questions[i][1];
        p = questions[i][2];
        int maxNumber = N - 1 + N * p + 1;
        V = 1100;
        if (haveDijkstraResults[source] == 0)
        {
            dijkstra(1100, source, dest);
        }
        else
        {
            // printf("i got here\n");
            printAnswer(dijkstraResults[source], dest);
        }
    }
}