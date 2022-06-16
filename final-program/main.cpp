#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "graph.h"

using namespace std;

int main() {
    // variables declaration
    ifstream matrix_file;
    vector<vector<int>> sorted_edge;
    string line, stemp;
    int vertices = 0, mst_weight = 0;
    double cable_price, pole_price;

    cout << "===================================" << endl;
    cout << "||     PROGRAM BIAYA MINIMUM     ||" << endl;
    cout << "===================================" << endl;

    // count vertices
    matrix_file.open("graph.csv");
    while(getline(matrix_file, line)) {
        vertices++;
    }
    matrix_file.close();

    // make 2d array for weight matrix
    int **matrix;
    matrix = (int**)malloc(vertices * sizeof(*matrix));
    for(int i = 0; i < vertices; i++) {
        matrix[i] = (int*)malloc(vertices * sizeof(int));
    }

    // add edges weight matrix into array 
    matrix_file.open("graph.csv");
    for(int i = 0; i < vertices; i++) {
        getline(matrix_file, line);
        stringstream stream(line);
        for(int j = 0; j < vertices; j++) {
            stream >> matrix[i][j];
            getline(stream, stemp, ';');
        }
    }
    matrix_file.close();

    // insert information for calculation
    cout << "Harga kabel/m\t: Rp";
    cin >> cable_price;
    cout << "Harga tiang/buah: Rp";
    cin >> pole_price;

    // output for weight matrix
    cout << endl << "Matrix bobot awal:" << endl;
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // make list of edges using vector
    for(int i = 0; i < vertices; i++) {
        for(int j = i; j < vertices; j++) {
            if(matrix[i][j] != 0) {
                sorted_edge.push_back({i, j, matrix[i][j]});
            }
        }
    }


    // sort edges vector by ascending
    vector<int> temp;
    for(int i = 0; i < vertices; i++) {
        int min_idx = i;
        for(int j = i + 1; j < vertices; j++) {
            if(sorted_edge[min_idx][2] > sorted_edge[j][2]) min_idx = j;
        }

        temp = sorted_edge[i];  
        sorted_edge[i] = sorted_edge[min_idx];
        sorted_edge[min_idx] = temp;
    }

    // make mst 2d array
    int **mst;
    mst = (int**)malloc(vertices * sizeof(*mst));
    for(int i = 0; i < vertices; i++) {
        mst[i] = (int*)malloc(vertices * sizeof(int));
    }

    // zero for mst
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            mst[i][j] = 0;
        }
    }

    // kruskal algorithm
    cout << endl << "List of edges:" << endl;
    for(int i = 0; i < sorted_edge.size(); i++) {
        mst[sorted_edge[i][0]][sorted_edge[i][1]]
            = mst[sorted_edge[i][1]][sorted_edge[i][0]]
            = sorted_edge[i][2];

        if(cycle_detection(vertices, mst)) {
            mst[sorted_edge[i][0]][sorted_edge[i][1]]
                = mst[sorted_edge[i][1]][sorted_edge[i][0]]
                = 0;
            continue;
        }

        mst_weight += sorted_edge[i][2];
        cout << sorted_edge[i][0] << " - " << sorted_edge[i][1] << " -> ";
        cout << sorted_edge[i][2] << endl;
    }

    // output for mst graph
    cout << endl << "MST Graph:" << endl;
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            cout << mst[i][j] << " ";
        }
        cout << endl;
    }

    // output for information
    cout << endl << "Informasi:" << endl;
    cout << "Panjang kabel\t: " << mst_weight << endl;
    cout << "Banyak tiang\t: " << vertices << endl << endl;

    printf("Biaya kabel\t: Rp%.2lf\n", mst_weight * cable_price);
    printf("Biaya tiang\t: Rp%.2lf\n", vertices * pole_price);
    printf("Biaya minimum yang harus dipersiapkan: Rp%.2lf\n",
        mst_weight * cable_price + vertices * pole_price);


    return 0;
}