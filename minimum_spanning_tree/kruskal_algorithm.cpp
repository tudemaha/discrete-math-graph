#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <math.h>
#include "graph.h"

using namespace std;

int main() {
    ifstream matrix_file;
    int vertices = 0;
    vector<vector<int>> sorted_edges;

    int buffer;
    matrix_file.open("graph.txt");
    while(!matrix_file.eof()) {
        matrix_file >> buffer;
        vertices++;
    }
    matrix_file.close();

    vertices = sqrt(vertices);
    int matrix[vertices][vertices];
    int mst[vertices][vertices];

    matrix_file.open("graph.txt");
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            matrix_file >> matrix[i][j];
        }
    }
    matrix_file.close();

    for(int i = 0; i < vertices; i++) {
        for(int j = i; j < vertices; j++) {
            if(matrix[i][j] != 0) {
                sorted_edges.push_back({i, j, matrix[i][j]});
            }
        }
    }

    for(int i = 0; i < vertices; i++) {
        int min_idx = i;
        for(int j = i + 1; j < vertices; j++) {
            if(sorted_edges[min_idx][2] > sorted_edges[j][2]) {
                min_idx = j;
            }
        }
        vector<int> temp = sorted_edges[i];
        sorted_edges[i] = sorted_edges[min_idx];
        sorted_edges[min_idx] = temp;
    }

    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            mst[i][j] = 0;
        }
    }

    for(int i = 0; i < vertices; i++) {
        mst[sorted_edges[i][0]][sorted_edges[i][1]]
            = mst[sorted_edges[i][1]][sorted_edges[i][0]]
            = sorted_edges[i][2];

        
    }

    for(int i = 0; i < sorted_edges.size(); i++) {
        for(int j = 0; j < 3; j++) {
            cout << sorted_edges[i][j] << " ";
        }
        cout << endl;
    }

    // cycle_detection(vertices, matrix);
    array<array<int, 2>> = {{1, 2}, {3, 4}};
    coout

    return 0;
}