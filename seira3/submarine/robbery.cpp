#include<iostream>
#include<bits/stdc++.h> 

using namespace std;

// C++ program for Kruskal's algorithm to find Minimum 
// Spanning Tree of a given connected, undirected and 
// weighted graph 

long int globalRed = 0, globalGreen = 0, globalYellow = 0;
long int V, E, a, b;
int c;

// Creating shortcut for an integer pair
struct edge{
	int cost;
	int start;
	int end;
	char color;
};

typedef struct edge edge;

vector <edge*> arr[50001];
const int N = 100000;
vector<int> graph[N];
vector<int> cycles[N];
int color[N];
int par[N];

// mark with unique numbers
int mark[N];

// store the numbers of cycle
int cyclenumber = 0;

// Function to mark the vertex with
// different colors for different cycles
void dfs_cycle(int u, int p, int color[],
			   int mark[], int par[], int &cyclenumber)
{

	// already (completely) visited vertex.
	if (color[u] == 2)
	{
		return;
	}

	// seen vertex, but was not completely visited -> cycle detected.
	// backtrack based on parents to find the complete cycle.
	if (color[u] == 1)
	{

		cyclenumber++;
		int cur = p;
		mark[cur] = cyclenumber;

		// backtrack the vertex which are
		// in the current cycle thats found
		while (cur != u)
		{
			globalYellow++;
			cur = par[cur];
			mark[cur] = cyclenumber;
		}
		return;
	}
	par[u] = p;

	// partially visited.
	color[u] = 1;

	// simple dfs on graph
	for(vector<edge*>::iterator it = arr[u].begin(); it!=arr[u].end();it++)
	{
		int v = *it.start;
		if(v==u){
			v = *it.end;
		}
		// if it has not been visited previously
		if (v == par[u])
		{
			continue;
		}
		dfs_cycle(v, u, color, mark, par, cyclenumber);
	}

	// completely visited.
	color[u] = 2;
}

// add the edges to the graph
void addEdge(int u, int v)
{
	graph[u].push_back(v);
	graph[v].push_back(u);
}

// Function to print the cycles
void printCycles(int edges, int mark[], int &cyclenumber)
{

	// push the edges that into the
	// cycle adjacency list
	for (int i = 1; i <= edges; i++)
	{
		if (mark[i] != 0)
			cycles[mark[i]].push_back(i);
	}

	// print all the vertex with same cycle
	for (int i = 1; i <= cyclenumber; i++)
	{
		// Print the i-th cycle
		cout << "Cycle Number " << i << ": ";
		for (int x : cycles[i])
			cout << x << " ";
		cout << endl;
	}
}

// Structure to represent a graph 
struct Graph 
{ 
	int V, E; 
	vector< edge > edges; 

	// Constructor 
	Graph(int V, int E) 
	{ 
		this->V = V; 
		this->E = E; 
	} 

	// Utility function to add an edge 
	vector<edge*> addEdge(int u, int v, int w, char c) 
	{ 
		edges.push_back({w, u, v, c}); 
		return edges.back();
	} 

}; 

	// Function to find MST using Kruskal's 
	// MST algorithm 
	int kruskalMST(); 





// To represent Disjoint Sets 
struct DisjointSets 
{ 
	int *parent, *rnk; 
	int n; 

	// Constructor. 
	DisjointSets(int n) 
	{ 
		// Allocate memory 
		this->n = n; 
		parent = new int[n+1]; 
		rnk = new int[n+1]; 

		// Initially, all vertices are in 
		// different sets and have rank 0. 
		for (int i = 0; i <= n; i++) 
		{ 
			rnk[i] = 0; 

			//every element is parent of itself 
			parent[i] = i; 
		} 
	} 

	// Find the parent of a node 'u' 
	// Path Compression 
	int find(int u) 
	{ 
		/* Make the parent of the nodes in the path 
		from u--> parent[u] point to parent[u] */
		if (u != parent[u]) 
			parent[u] = find(parent[u]); 
		return parent[u]; 
	} 

	// Union by rank 
	void merge(int x, int y) 
	{ 
		x = find(x), y = find(y); 

		/* Make tree with smaller height 
		a subtree of the other tree */
		if (rnk[x] > rnk[y]) 
			parent[y] = x; 
		else // If rnk[x] <= rnk[y] 
			parent[x] = y; 

		if (rnk[x] == rnk[y]) 
			rnk[y]++; 
	} 
}; 

// Create disjoint sets 
DisjointSets ds(V); 

/* Functions returns weight of the MST*/

int Graph::kruskalMST() 
{ 
	int mst_wt = 0; // Initialize result 

	// Sort edges in increasing order on basis of cost 
	sort(edges.begin(), edges.end());

	// Iterate through all sorted edges
	vector<edge>::iterator it, startIterator, endIterator;
	// for (it=edges.begin(); it!=edges.end(); it++)
	// {

	while (it != edges.end())
	{
		startIterator = it;
		endIterator = it;
		while ((endIterator + 1)->cost == startIterator->cost)
		{
			endIterator++;
		}

		computeGraph(startIterator, endIterator);
	}
}

// return mst_wt;

void checkForCircle(){


}

void computeGraph(vector<edge>::iterator startIterator, vector<edge>::iterator endIterator)
{
	vector<edge>::iterator it;
	it = startIterator;
	while (it <= endIterator)
	{
		int u = it->start;
		int v = it->end;
		int set_u = ds.find(u);
		int set_v = ds.find(v);

		// Check if the selected edge is creating
		// a cycle or not (Cycle is created if u
		// and v belong to same set)
		if (set_u == set_v)
		{
			// Current edge will be in the MST
			// so print it
			// cout << u << " - " << v << endl;

			// Merge two sets
			// ds.merge(set_u, set_v);
			it->color = 'r';
			globalRed++;
		}
		it++;
	}
	// Now we have excluded the red edges
	it = startIterator;
	while( it <= endIterator){

		if(it->color != 'r') {

			int u = it->start;
			int v = it->end;
			int set_u = ds.find(u);
			int set_v = ds.find(v);
			if( set_u != set_v){
				ds.merge(set_u, set_v);
			}
			else{

				// checkForCircle();
				// dfs(u)
				// call DFS to mark the cycles
				dfs_cycle(1, 0, color, mark, par, cyclenumber);
			}
		}
	}
	contractCurrentEdges();
}




// Driver program to test above functions 
int main() 
{ 
	/* Let us create above shown weighted 
	and unidrected graph */
    scanf("%ld",&V);
    scanf("%ld",&E);

	Graph g(V, E); 
    
    for(long int i = 0; i < E; i++)
    {
        scanf("%ld",&a);
        scanf("%ld",&b);
        scanf("%d",&c);
		arr[a ] = g.addEdge(a, b, c, 'r');
		arr[b ] = g.addEdge(a, b, c, 'r');
		
	}
	arr[0] = g.addEdge(0,0,0,'g');
    
	
	g.kruskalMST(); 
	globalGreen = V - globalRed - globalYellow;
	printf("%ld\n%ld\n%ld",globalGreen,globalRed,globalYellow);
	return 0; 
} 
