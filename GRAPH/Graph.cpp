#pragma once
#include "Graph.h"

#define MAX 1000

Graph::Graph(string fileName ){
    ifstream fi;
    fi.open(fileName, ifstream::in);
    string tmp = "";
    getline(fi, tmp);
    this->v = stoi(tmp);
    this->matrix = new int*[this->v];
    for (int i = 0; i < this->v; ++i) this->matrix[i] = new int[v];
    char c;
    for (int i = 0; i < this->v; ++i) {
        int j = 0;
        while (j < this->v) {
            tmp = "";
            do {
                c = fi.get();
                tmp += c; 
            } while (c != ' ' && c != '\n' && fi.good());
            tmp.pop_back();
            this->matrix[i][j] = stoi(tmp);
            ++j;
        }
    }
    fi.close();
}

Graph::~Graph() {
    for (int i = 0; i < this->v; ++i) delete[](this->matrix[i]);
    delete[]matrix;
}

void Graph::minPathDij(int** &m, int i, int j, int root) {
    if (i == 1) {
        cout << root;
        return;
    }
    if (m[i][j] == m[i - 1][j]) minPathDij(m, i - 1, j, root);
    else {
        
        minPathDij(m, i - 1, m[i][0] + 1, root);
        cout << "->" << m[i][0];
    }
    return;
}

void Graph::Dijkstra(int root) {
    int** dijkstra = new int* [this->v + 1];            //Dijkstra matrix
    bool* check = new bool[this->v];                    
    for (int i = 0; i <= this->v; ++i) dijkstra[i] = new int[this->v + 1]; 
    for (int i = 0; i < this->v; ++i) check[i] = 0;
    dijkstra[0][0] = -1;
    int ver = root, verToRoot = 0;
    for (int j = 1; j <= this->v; ++j)
        if (j - 1 == root) dijkstra[0][j] = 0;
        else dijkstra[0][j] = MAX;
    for (int i = 1; i <= this->v; ++i) {
        int min = MAX, minj = 0;
        check[ver] = 1;
        for (int j = 0; j <= this->v; ++j) {
            if (j == 0) dijkstra[i][j] = ver;
            else {
                if (this->matrix[ver][j - 1] == 0 || this->matrix[ver][j - 1] + verToRoot > dijkstra[i - 1][j]) dijkstra[i][j] = dijkstra[i - 1][j];
                else dijkstra[i][j] = this->matrix[ver][j - 1] + verToRoot;
                if (min >= dijkstra[i][j] && !check[j - 1]) {
                    min = dijkstra[i][j];
                    minj = j - 1;
                }
            }
        }
        verToRoot = min;
        ver = minj;
    }
        
    cout << "Shortest Path from " << root << " to all" << endl;
    cout << "Vertex \t minPath \t Path" << endl;
    for (int j = 0; j < this->v; ++j) {
        cout << j <<"\t " << dijkstra[this->v][j + 1] << "\t\t ";
        minPathDij(dijkstra, this->v, j + 1, root);
        if (j != root) cout << "->" << j;
        cout << endl;
    }
    for (int i = 0; i < this->v; ++i) delete[]dijkstra[i];
    delete[]dijkstra;
    delete[]check;
}

void Graph::display() {
    for (int i = 0; i < this->v; ++i)
        for (int j = 0; j < this->v; ++j) cout << this->matrix[i][j];
}