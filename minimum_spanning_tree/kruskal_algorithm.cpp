#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "graph.h"

using namespace std;

int main() {
    ifstream matrix_file;
    int vertices = 0;
    vector<vector<int>> sorted_edges;
    int mst_weight = 0;
    int buffer;
    
    matrix_file.open("graph.txt");
    while(!matrix_file.eof()) {
        matrix_file >> buffer;
        vertices++;
    }
    matrix_file.close();
    vertices = sqrt(vertices);

    int **matrix;
    matrix = (int**)malloc(vertices * sizeof(*matrix));
    for(int i = 0; i < vertices; i++) {
        matrix[i] = (int*)malloc(vertices * sizeof(int));
    }

    matrix_file.open("graph.txt");
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            matrix_file >> matrix[i][j];
        }
    }
    matrix_file.close();

    if(!connected_graph(vertices, matrix)) {
        cout << "Graph tidak terhubung, proses tidak dapat dilanjutkan." << endl;
        exit(0);
    }

    for(int i = 0; i < vertices; i++) {
        for(int j = i; j < vertices; j++) {
            if(matrix[i][j] != 0) {
                sorted_edges.push_back({i, j, matrix[i][j]});
            }
        }
    }

    vector<int> temp;
    for(int i = 0; i < sorted_edges.size(); i++) {
        int min_idx = i;
        for(int j = i + 1; j < sorted_edges.size(); j++) {
            if(sorted_edges[min_idx][2] > sorted_edges[j][2]) {
                min_idx = j;
            }
        }
        temp = sorted_edges[i];
        sorted_edges[i] = sorted_edges[min_idx];
        sorted_edges[min_idx] = temp;
    }


    int **mst;
    mst = (int**)malloc(vertices * sizeof(*mst));
    for(int i = 0; i < vertices; i++) {
        mst[i] = (int*)malloc(vertices * sizeof(int));
    }
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            mst[i][j] = 0;
        }
    }

    cout << "Matriks ketetanggan awal:" << endl;
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << endl << "Kruskal's MST Edges:" << endl;
    for(int i = 0; i < sorted_edges.size(); i++) {
        mst[sorted_edges[i][0]][sorted_edges[i][1]]
            = mst[sorted_edges[i][1]][sorted_edges[i][0]]
            = sorted_edges[i][2];

        if(cycle_detection(vertices, mst)) {
            mst[sorted_edges[i][0]][sorted_edges[i][1]]
                = mst[sorted_edges[i][1]][sorted_edges[i][0]]
                = 0;
            continue;
        }
        mst_weight += sorted_edges[i][2];
        cout << sorted_edges[i][0] << "-" << sorted_edges[i][1] << " -> ";
        cout << sorted_edges[i][2] << endl;
    }

    
    cout << endl << "Kruskal's MST:" << endl;
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            cout << mst[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl << "Kruskal's MST Weight: " << mst_weight << endl;

    return 0;
}