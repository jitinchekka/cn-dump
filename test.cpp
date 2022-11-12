#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<pair<int, int>> g[N];

void dijkstra(int src, int n)
{
	vector<bool> vis(N, false);
	vector<int> dis(N, 1e9);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // pair.first=dist,pq.second=vertex
	dis[src] = 0;
	pq.push({0, src});
	while (!pq.empty())
	{
		int dist = pq.top().first;
		int vertex = pq.top().second;
		pq.pop();
		if (vis[vertex])
			continue;
		vis[vertex] = true;
		for (auto child : g[vertex])
		{
			int child_vertex = child.second;
			int weight = child.first;
			if (dis[child_vertex] > dis[vertex] + weight)
			{
				dis[child_vertex] = dis[vertex] + weight;
				pq.push({dis[child_vertex], child_vertex});
			}
		}
	}
}

int main()
{
	return 0;
}