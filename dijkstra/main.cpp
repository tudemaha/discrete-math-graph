#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int main() {
    ifstream matrix_file;
    int vertices, source;

    matrix_file.open("graph.txt");
    int buffer;
    while(!matrix_file.eof()) {
        matrix_file >> buffer;
        vertices++;
    }
    matrix_file.close();
    vertices = sqrt(vertices);

    int matrix[vertices][vertices];

    matrix_file.open("graph.txt");
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            matrix_file >> matrix[i][j];
        }
    }
    matrix_file.close();

    int edges_weight[vertices];
    int status[vertices];
    for(int i = 0; i < vertices; i++) {
        edges_weight[i] = 999;
        status[i] = 0;
    }

    cout << "Masukkan vertex source: ";
    cin >> source;

    int current = source;
    edges_weight[current] = 0;
    for(int i = 0; i < vertices; i++) {
        status[current] = 1;
        for(int j = 0; j < vertices; j++) {
            if(matrix[current][j] != 0 and status[j] == 0) {
                if(matrix[current][j] < edges_weight[j]) {
                    edges_weight[j] = edges_weight[current] + matrix[current][j];
                }
            }
        }


    }

    
    for(int i = 0; i < vertices; i++) {
        cout << status[i] << " ";
    }


    // for(int i = 0; i < vertices; i++) {
    //     for(int j = 0; j < vertices; j++) {
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}