#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int main() {
    ifstream matrix_file;
    int vertices = 0, source, current, index, temp;

    matrix_file.open("graph.txt");
    short buffer;
    while(!matrix_file.eof()) {
        matrix_file >> buffer;
        vertices++;
    }
    vertices = sqrt(vertices);
    matrix_file.close();

    short matrix[vertices][vertices];
    bool status[vertices];
    int path_weight[vertices];

    matrix_file.open("graph.txt");
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            matrix_file >> matrix[i][j];
        }
    }
    matrix_file.close();

    cout << "Matrix bobot:" << endl;
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    insert_source:
    cout << endl << "Masukkan source vertex: ";
    cin >> source;
    if((source < 1) or (source > vertices)) {
        cout << "Vertex source di luar batas" << endl;
        goto insert_source;
    }
    source--;

    for(int i = 0; i < vertices; i++) {
        status[i] = false;
        path_weight[i] = 999;
    }

    // for(int i = 0; i < vertices; i++) {
    //     cout << status[i] << " " << path_weight[i] << endl;
    // }

    current = source;
    path_weight[current] = 0;
    for(int i = 0; i < vertices; i++) {
        status[current] = 1;
        for(int j = 0; j < vertices; j++) {
            if(matrix[current][j] != 0 and status[j] == 0) {
                if(path_weight[current] + matrix[current][j] < path_weight[j]) {
                    path_weight[j] = path_weight[current] + matrix[current][j];
                }
            }
        }

        temp = 999;
        for(int j = 0; j < vertices; j++) {
            if((status[j] == false) and (temp > path_weight[j])) {
                temp = path_weight[j];
                index = j;
            }
        }
        current = index;
        // cout << current << " ";
    }

    cout << endl << "Daftar jarak:" << endl;
    for(int i = 0; i < vertices; i++) {
        cout << source + 1 << " - " << i + 1 << " ==> " << path_weight[i] << endl;;
    }

    return 0;
}