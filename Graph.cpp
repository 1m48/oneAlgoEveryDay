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
        cout << "delete successfully";
}

int** Graph::Dijkstra(int root) {
        int** dijkstra = new int* [this->v + 1];
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
                    if (this->matrix[ver][j - 1] == 0) dijkstra[i][j] = dijkstra[i - 1][j];
                    else if (this->matrix[ver][j - 1] + verToRoot < dijkstra[i - 1][j]) dijkstra[i][j] = this->matrix[ver][j - 1] + verToRoot;
                    else dijkstra[i][j] = dijkstra[i - 1][j];
                    if (min >= dijkstra[i][j] && !check[j - 1]) {
                        min = dijkstra[i][j];
                        minj = j - 1;
                    }
                }
            }
            verToRoot = min;
            ver = minj;
        }

        
        for (int i = 0; i <= this->v; ++i) {
            for (int j = 0; j <= this->v; ++j) cout << dijkstra[i][j] << " ";
            cout << endl;
        }
        return dijkstra;
}

void Graph::display() {
    for (int i = 0; i < this->v; ++i)
        for (int j = 0; j < this->v; ++j) cout << this->matrix[i][j];
}