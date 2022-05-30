#include <iostream>
#include <string>

#include "Graph.h"

int main() {
	Graph <std::string, int> graph;
	graph.Add("A", "B", 5);
	graph.Add("A", "C", 6);
	graph.Add("B", "C", 1);
	graph.Add("B", "D", 7);
	graph.Add("C", "D", 2);

	Result_BellmanFord<std::string> res = graph.BellmanFord("B", "D");

	std::cout << res.weight << "\n";
	for (int i = 0; i < res.path.size(); i++)
		std::cout << res.path[i] << " ";

	std::cout << "\n\n";
	std::vector<std::pair<std::string, std::string>> a = graph.Breadth_First_Search("A");
	for (int i = 0; i < a.size(); i++)
		std::cout << a[i].first << " -> " << a[i].second << "\n";
	std::cout << "\n";

	graph.Add_Vertex("M");
	graph.Add("M", "A", 4);
	graph.Add("C", "M", 8);

	Result_BellmanFord<std::string> first = graph.BellmanFord("B", "M");

	std::cout << first.weight << "\n";
	for (int i = 0; i < first.path.size(); i++)
		std::cout << first.path[i] << " ";
	std::cout << "\n";

	graph.Delete_Vertex("M");

	Result_BellmanFord<std::string> second = graph.BellmanFord("B", "M");
	std::cout << "\n";
	std::cout << second.weight << "\n";
	for (int i = 0; i < second.path.size(); i++)
		std::cout << second.path[i] << " ";

	graph.Delete_Edge("A", "K", 2);

	return 0;
}