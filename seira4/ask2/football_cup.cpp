#include <iostream>
#include <stdio.h>

using namespace std;

// C++ Implementation of Kosaraju's algorithm to print all SCCs
#include <iostream>
#include <list>
#include <stack>

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

long long int countMax = 0;
class Graph
{
    int V;          // No. of vertices
    list<int> *adj; // An array of adjacency lists

    // Fills Stack with vertices (in increasing order of finishing
    // times). The top element of stack has the maximum finishing
    // time
    void fillOrder(int v, bool visited[], stack<int> &Stack);

    // A recursive function to print DFS starting from v
    void DFSUtil(int v, bool visited[]);

  public:
    Graph(int V);
    void addEdge(int v, int w);

    // The main function that finds and prints strongly connected
    // components
    void printSCCs();

    // Function that returns reverse (or transpose) of this graph
    Graph getTranspose();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

// A recursive function to print DFS starting from v
void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    // cout << v << " ";
    countMax++;
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
        {
            DFSUtil(*i, visited);
        }
}

Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < V; v++)
    {
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack)
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            fillOrder(*i, visited, Stack);

    // All vertices reachable from v are processed by now, push v
    Stack.push(v);
}

// The main function that finds and prints all strongly connected
// components
void Graph::printSCCs()
{
    stack<int> Stack;

    // Mark all the vertices as not visited (For first DFS)
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Fill vertices in stack according to their finishing times
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            fillOrder(i, visited, Stack);

    // Create a reversed graph
    Graph gr = getTranspose();

    // Mark all the vertices as not visited (For second DFS)
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Now process all vertices in order defined by Stack
    while (Stack.empty() == false)
    {
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();

        // Print Strongly connected component of the popped vertex
        if (visited[v] == false)
        {
            gr.DFSUtil(v, visited);
        }
        break;
    }
}

// // Driver program to test above functions
// int main()
// {
//     // Create a graph given in the above diagram
//     g.addEdge(0, 2);
//     g.addEdge(2, 1);
//     g.addEdge(0, 3);
//     g.addEdge(3, 4);

//     cout << "Following are strongly connected components in "
//             "given graph \n";

//     return 0;
// }

int main(void)
{
    int n = read_int();
    // scanf("%d",&n);
    // Create graph
    Graph g(n);
    int firstNumber,w;
    for (int i = 0 ; i < n ; i++ )
    {
        // scanf("%d",&d[i][0]);
        firstNumber = read_int();
        for (int j = 1 ; j <= firstNumber; j++)
        {
            // scanf("%d",&d[i][j]);
            w = read_int();
            g.addEdge(w - 1, i);
        }
    }
    g.printSCCs();
    printf("%lld\n",countMax);
}