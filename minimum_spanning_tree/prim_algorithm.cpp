#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "graph.h"

using namespace std;

int main() {
    ifstream matrix_file;
    int vertices = 0;
    int buffer;
    int **matrix, **mst;
    int mst_weight = 0;
    vector<vector<int>> edges;
    vector<int> used_vertices;
    
    matrix_file.open("graph.txt");
    while(!matrix_file.eof()) {
        matrix_file >> buffer;
        vertices++;
    }
    matrix_file.close();
    vertices = sqrt(vertices);

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

    cout << "Matriks ketetanggaan awal:" << endl;
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    for(int i = 0; i < vertices; i++) {
        for(int j = i; j < vertices; j++) {
            if(matrix[i][j] != 0) {
                edges.push_back({i, j, matrix[i][j]});
            }
        }
    }

    mst = (int**)malloc(vertices * sizeof(*mst));
    for(int i = 0; i < vertices; i++) {
        mst[i] = (int*)malloc(vertices * sizeof(int));
    }

    cout << endl << "Prim's MST Edges:" << endl;
    int min_index = 0;
    for(int i = 0; i < edges.size(); i++) {
        if(edges[min_index][2] > edges[i][2]) {
            min_index = i;
        }
    }
    mst[edges[min_index][0]][edges[min_index][1]]
        = mst[edges[min_index][1]][edges[min_index][0]]
        = edges[min_index][2];

    mst_weight += edges[min_index][2];
    cout << edges[min_index][0] << "-" << edges[min_index][1];
        cout << " -> " << edges[min_index][2] << endl;
        
    used_vertices.push_back(edges[min_index][0]);
    used_vertices.push_back(edges[min_index][1]);
    edges.erase(edges.begin() + min_index);

    int weight_before;
    while(!edges.empty()) {
        weight_before = edges[min_index][2];
        min_index = 0;
        for(int i = 0; i < edges.size(); i++) {
            if((edges[min_index][2] > edges[i][2]) and (edges[i][2] > weight_before)) {
                min_index = i;
            }
        }
        
        if(neighbor_checking(used_vertices, edges[min_index][0])
            or neighbor_checking(used_vertices, edges[min_index][1])) {
                mst[edges[min_index][0]][edges[min_index][1]]
                    = mst[edges[min_index][1]][edges[min_index][0]]
                    = edges[min_index][2];

                if(cycle_detection(vertices, mst)) {
                    mst[edges[min_index][0]][edges[min_index][1]]
                            = mst[edges[min_index][1]][edges[min_index][0]]
                            = 0;
                } else {
                    mst_weight += edges[min_index][2];
                    cout << edges[min_index][0] << "-" << edges[min_index][1];
                    cout << " -> " << edges[min_index][2] << endl;

                    used_vertices.push_back(edges[min_index][0]);
                    used_vertices.push_back(edges[min_index][1]);
                }

                edges.erase(edges.begin() + min_index);
        }        
    }

    cout << endl << "Prim's MST:" << endl;
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            cout << mst[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl << "Prim's MST Weight: " << mst_weight << endl;

    return 0;
}