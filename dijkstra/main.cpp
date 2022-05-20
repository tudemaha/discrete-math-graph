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

    cout << "Matriks bobot:" << endl;
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    int edges_weight[vertices];
    int status[vertices];
    for(int i = 0; i < vertices; i++) {
        edges_weight[i] = 999;
        status[i] = 0;
    }

    cout << "Masukkan vertex source: ";
    cin >> source;

    int current = source;
    int temp, index;
    edges_weight[current] = 0;
    for(int i = 0; i < vertices; i++) {
        status[current] = 1;
        for(int j = 0; j < vertices; j++) {
            if(matrix[current][j] != 0 and status[j] == 0) {
                if(edges_weight[current] + matrix[current][j] < edges_weight[j]) {
                    edges_weight[j] = edges_weight[current] + matrix[current][j];
                }
            }
        }

        cout << endl << endl;
        for(int i = 0; i < vertices; i++) {
            cout << edges_weight[i] << " ";
        }

        temp = 999;
        for(int j = 0; j < vertices; j++) {
            if(status[j] == 0 and temp > edges_weight[j]) {
                temp = edges_weight[j];
                index = j;
            }
        }
        current = index;
        cout << "  " << current;
    }

    cout << endl << endl;
    for(int i = 0; i < vertices; i++) {
        cout << edges_weight[i] << " ";
    }


    // for(int i = 0; i < vertices; i++) {
    //     for(int j = 0; j < vertices; j++) {
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}