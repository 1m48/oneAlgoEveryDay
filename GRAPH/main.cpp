#include "Graph.cpp"

using namespace std;

int main() {
    Graph graph("testcase.txt");
    graph.Dijkstra(1);
    graph.~Graph();
}