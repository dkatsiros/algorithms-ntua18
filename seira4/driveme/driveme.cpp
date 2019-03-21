#include <stdio.h>
#include <iostream>

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

long int N,M,K,Q;
int u,v,p;
long int graph[1000][1000];
long int minDist[1000][1000];
int questions[10000][3];

void setGraphZeros()
{
    for(int i = 0; i < 1000; i++)
    {
        for(int j = 0; j < 1000; j++)
        {
            graph[i][j] = 0;
        }
        
    }
    
}

// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph

#include <stdio.h>
#include <limits.h>
int V;

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance array
int printSolution(int dist[], int n)
{
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d tt %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int V , int src, int dest)
{
    int dist[V]; // The output array. dist[i] will hold the shortest
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

    // print the constructed distance array
    // printSolution(dist, V);
    // save Solutions
    // for( int i=1 ; i< V; i++)
    // {
    //     minDist[src][i] = findMin(dist[i],minDist)
    // }
    int min = dist[dest];
    for(int i=0;i<=p ;i++)
    {
        if( dist[ dest + i* N ] < min)
        {
            min = dist[dest + i*N];
        }
        
    }
    if (min != INT_MAX )
    {
        printf("%ld\n",min);
    }
    else
    {
        printf("IMPOSSIBLE\n");
    }
    
}

// driver program to test above function
// int main()
// {
//     /* Let us create the example graph discussed above */
//     int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
//                        {4, 0, 8, 0, 0, 0, 0, 11, 0},
//                        {0, 8, 0, 7, 0, 4, 0, 0, 2},
//                        {0, 0, 7, 0, 9, 14, 0, 0, 0},
//                        {0, 0, 0, 9, 0, 10, 0, 0, 0},
//                        {0, 0, 4, 14, 10, 0, 2, 0, 0},
//                        {0, 0, 0, 0, 0, 2, 0, 1, 6},
//                        {8, 11, 0, 0, 0, 0, 1, 0, 7},
//                        {0, 0, 2, 0, 0, 0, 6, 7, 0}};

//     dijkstra(graph, 0);

//     return 0;
// }

int main() 
{
    N = read_int();
    M = read_int();
    K = read_int();
    Q = read_int();

    setGraphZeros();
    long int dUV;

    for(int i = 0; i < M; i++)
    {
        u = read_int() - 1 ;
        v = read_int() - 1;
        scanf("%ld",&dUV);
        graph[u][v] = dUV;
        for(int k = 1 ; k <= K ; k++)
        {
            graph[u + N * k][v + N *k ] = dUV;
            // x,y e [1 eos v + k-Nades]
            graph[v + N*(k-1)][u + N*k ] = dUV;
        }
    }

    for(int i = 0; i < Q; i++)
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
        int maxNumber = N - 1 + N * p   + 1;
        V = maxNumber;
        dijkstra(maxNumber,source,dest);
    }
}