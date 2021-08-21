#pragma once
#include <iostream>
#include <fstream>
#include <string>

#define MAX 1000

using namespace std;

class Graph {
    int v;
    int** matrix;
public:
    Graph(string);
    ~Graph();
    void minPathDij(int** &, int , int, int);
    void Dijkstra(int);
    void display();
};