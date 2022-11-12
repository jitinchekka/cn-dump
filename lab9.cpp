#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;

typedef long long ll;
typedef long double ld;
#define pb push_back
#define fast_cin()                    \
	ios_base::sync_with_stdio(false); \
	cin.tie(NULL);                    \
	cout.tie(NULL)

const int mod = 1e9 + 7;
void readInputFile()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
}
const int N = 1e5 + 10;
vector<pair<int, int>> g[N]; // first is node, second is weight

void dijkstra(int source, int n)
{
	vector<int> vis(N, 0);
	vector<int> dist(N, 1e9);
	// vector<int> parent(N, -1);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // first is dist, second is node
	dist[source] = 0;
	pq.push({0, source});
	while (!pq.empty())
	{
		int node = pq.top().second;
		int dis = pq.top().first;
		pq.pop();
		if (vis[node])
			continue;
		vis[node] = true;
		for (auto child : g[node])
		{
			int child_vertex = child.first;
			int weight = child.second;
			// Relax the edge
			if (dist[node] + weight < dist[child_vertex])
			{
				dist[child_vertex] = dist[node] + weight;
				parent[child_vertex] = node;
				pq.push({dist[child_vertex], child_vertex});
			}
		}
	}

	// Print the shortest path
	/*for (int i = 1; i <= n; i++)
	{
		vector<int> path;
		int node = i;
		while (node != -1)
		{
			path.pb(node);
			node = parent[node];
		}
		reverse(path.begin(), path.end());
		cout << "Shortest path from " << source << " to " << i << " is: ";
		for (auto x : path)
			cout << x << " ";
	}*/
	for (int i = 1; i <= n; i++)
	{
		if (dist[i] == 1e9)
			cout << i << "\t\t"
				 << "INF";
		else
			cout << i << "\t\t" << dist[i] << endl;
	}
}

int main()
{
	int n, m;
	cout << "Enter the number of vertices and edges\n";
	cin >> n >> m;
	cout << "Enter all the edges in the form of source, destination and weight\n";
	for (int i = 0; i < m; i++)
	{
		int x, y, wt;
		cin >> x >> y >> wt;
		g[x].pb({y, wt});
	}
	for (int i = 1; i <= n; i++)
	{
		cout << "The routing table of router " << i << endl;
		cout << "Destination\tCost\n";
		dijkstra(i, n);
	}

	return 0;
}