//Nischal Pradyoth
//CS20B1109

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

// Number of vertices in the graph
int V;

// A utility function to find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree
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
void printSolution(int dist[])
{
	printf("Vertex \t\t Distance from Source\n");
	for (int i = 0; i < V; i++)
		printf("%d \t\t\t\t %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source shortest path algorithm for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
	int dist[V]; // The output array. dist[i] will hold the shortest distance from src to i

	bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; count++) {
		// Pick the minimum distance vertex from the set of vertices not yet processed. u is always equal to src in the first iteration.
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < V; v++)

			// Update dist[v] only if is not in sptSet,there is an edge from u to v, and total weight of path from src to v through u is smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

	// print the constructed distance array
	printSolution(dist);
}

int main()
{
    //taking input
    printf("Enter the value of V:");
    scanf("%d",&V);
    int graph[V][V];

    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            graph[i][j]=0;
        }
    }
    int edges,node1,node2,distance;
    printf("Enter the number of edges:");
    scanf("%d",&edges);

    printf("Enter in this format:\n");
    printf("Node1\tNode2\tDistance:\n");
    for(int i=0;i<edges;i++){
        scanf("%d %d %d",&node1,&node2,&distance);
        graph[node1][node2]=distance;
        graph[node2][node1]=distance;
    }

	dijkstra(graph, 0);

	return 0;
}