#include <iostream>
#include <string>

#include "Graph.h"

int main() {
	Graph <std::string, int> graph;
	graph.Add("A", "B", 5);
	graph.Add("A", "C", 6);
	graph.Add("B", "C", -2);
	graph.Add("B", "D", 7);
	graph.Add("C", "D", 2);


	return 0;
}