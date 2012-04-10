#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

void dfs(const std::vector<std::vector<int>>& graph,
		 int v,
		 std::vector<char>& visited,
		 std::vector<std::pair<int, int>>& cycles) 
{
	visited[v] = 1;
	for (size_t i = 0; i < graph[v].size(); ++i) {
		int u = graph[v][i];
		if (visited[u] == 0) {
			dfs(graph, u, visited, cycles);
		} else if (visited[u] == 2) {
			cycles.push_back(std::make_pair(u, v));
		}
	}
	visited[v] = 2;
}

void smartDfs(const std::vector<std::vector<int>>& graph,
			  int start,
			  std::vector<std::pair<int, int>>& cycles,
			  std::vector<int>& components) 
{
	std::vector<char> visited(graph.size(), 0);

	for (size_t i = start; i < graph.size(); ++i) {
		if (visited[i] == 0) {
			components.push_back(i);
			dfs(graph, i, visited, cycles);
		}
	}
}

int main() 
{
	int n;
	cin >> n;

	std::vector<std::vector<int>> graph(n+1, std::vector<int>());
	for (size_t i = 0; i < (size_t)n-1; ++i) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	std::vector<std::pair<int, int>> cycles;
	std::vector<int> components;
	smartDfs(graph, 1, cycles, components);

	cout << cycles.size() << endl;
	for (size_t i = 0; i < cycles.size(); ++i) {
		cout << cycles[i].first		<< " "
			 << cycles[i].second	<< " "
			 << components[i]		<< " "
			 << components[i + 1]
			 << endl;
	}

	return 0;
}