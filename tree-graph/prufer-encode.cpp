#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int main() {
    // program header
    cout << "===== PRUFER ENCODING =====" << endl;
    cout << "===========================" << endl << endl;

    // ifstream object
    ifstream matrix_file;

    // count vertex
    matrix_file.open("adjacency-matrix.txt");
    int vertex = 0, buffer;
    while(!matrix_file.eof()) {
        matrix_file >> buffer;
        vertex++;
    }
    vertex = sqrt(vertex);
    matrix_file.close();

    // make adjacency matrix
    matrix_file.open("adjacency-matrix.txt");
    int matrix[vertex][vertex];
    for(int i = 0; i < vertex; i++) {
        for(int j = 0; j < vertex; j++) {
            matrix_file >> matrix[i][j];
        }
    }
    matrix_file.close();

    // show adjacency matrix
    cout << "Matrix ketetanggan:" << endl;
    for(int i = 0; i < vertex; i++) {
        for(int j = 0; j < vertex; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // direction and loop check
    bool direction = false;
    bool loop = false;
    for(int i = 0; i < vertex; i++) {
        for(int j = 0; j < vertex; j++) {
            if(matrix[i][j] != matrix[j][i]) {
                direction = true;
                break;
            }
        }
        if(matrix[i][i] > 0) loop = true;
    }
    if(direction) {
        cout << endl << "Graph berarah! Proses tidak dapat dilanjutkan." << endl;
        exit(0);
    }
    if(loop) {
        cout << endl << "Graph memiliki loop! Proses tidak dapat dilanjutkan." << endl;
        exit(0);
    }

    // connected graph
    int helper_matrix[vertex];
    bool connect = true;
    for(int i = 0; i < vertex; i++) {
        helper_matrix[i] = matrix[0][i];
    }
    
    for(int i = 0; i < vertex; i++) {
        if(helper_matrix[i] == 1) {
            for(int j = 0; j < vertex; j++) {
                if((matrix[i][j] == 1) and helper_matrix[j] == 0) helper_matrix[j] = 1;
            }
        }
    }

    for(int i = 0; i < vertex; i++) {
        // cout << helper_matrix[i] << " ";
        if(helper_matrix[i] == 0) {
            connect = false;
            break;
        }
    }
    if(!connect) {
        cout << endl << "Graph tidak terhubung! Proses tidak dapat dilanjutkan." << endl;
        exit(0);
    }

    // circuit check

    // deg count
    int degree[vertex];
    for(int i = 0; i < vertex; i++) {
        degree[i] = 0;
        for(int j = 0; j < vertex; j++) {
            degree[i] += matrix[i][j];
        }
    }

    // prufer enocde
    int prufer[vertex - 2];
    int count = 0;
    
    while(count < vertex - 2) {
        for(int i = 0; i < vertex; i++) {
            if(degree[i] == 1) {
                (degree[i])--;
                for(int j = 0; j < vertex; j++) {
                    if(matrix[i][j] == 1) {
                        prufer[count] = j + 1;
                        matrix[i][j]--;
                        matrix[j][i]--;
                        (degree[j])--;
                        break;
                    }
                }
                break;
            }
        }
        count++;
    }

    cout << endl << "Kode prufer: ";
    for(int i = 0; i < vertex - 2; i++) {
        cout << prufer[i] << " ";
    }

    return 0;

}