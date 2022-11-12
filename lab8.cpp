// Author: Jitin
// Roll number: CS20B1075
// Distance vector routing algorithm
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
const int N = 1e5 + 10;
vector<pair<int, int>> g[N]; //{destination, weight}

// Bellman-Ford algorithm n = number of vertices, m = number of edges, s = source
// Find the path from s to all other vertices
int par[N] = {-1}; // parent of each vertex
void bellman_ford(int n, int m, int s)
{
	memset(par, -1, sizeof(par));
	vector<int> dist(n + 1, 1e9); // initialize distance of all vertices to infinity
	dist[s] = 0;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			for (auto e : g[j])
			{
				int v = e.first;
				int w = e.second;
				if (dist[j] + w < dist[v])
				{
					dist[v] = dist[j] + w;
					par[v] = j;
				}
			}
		}
	}

	for (int i = 1; i <= n; i++)
	{
		vector<int> path;
		int cur = i;
		while (cur != -1)
		{
			path.push_back(cur);
			cur = par[cur];
		}
		reverse(path.begin(), path.end());
		if (path.size() == 1)
			cout << i << "\t\t" << dist[i] << "\t\t" << path[0] << endl;
		else
			cout << i << "\t\t" << dist[i] << "\t\t" << path[1] << endl;
	}
}
int main()
{
	int n, e;
	cout << "Enter the number of vertices and edges: \n";
	cin >> n >> e;
	cout << "Enter the source, destination edges and their weights: \n";
	for (int i = 0; i < e; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	cout << "Running Bellman-Ford algorithm on the given graph" << endl;

	// Printing routing table
	for (int i = 1; i <= n; i++)
	{
		cout << "Routing table of " << i << endl;
		cout << "Desination\tCost\tNext Hop" << endl;
		bellman_ford(n, e, i);
		cout << endl;
	}

	return 0;
}