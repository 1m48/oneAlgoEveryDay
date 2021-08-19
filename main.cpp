#include "Graph.cpp"

using namespace std;

int main() {
    Graph graph("testcase.txt");
    graph.Dijkstra(0);
    graph.~Graph();
}