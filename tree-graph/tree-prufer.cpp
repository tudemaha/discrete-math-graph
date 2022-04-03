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
    matrix_file.open("adjacency-matrix.txt");

    // count vertex
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
    int prufer_count = vertex - 2;
    int prufer[prufer_count];
    int count = 0;
    
    while(count < prufer_count) {
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

    // cout prufer code
    cout << endl << "Kode prufer: ";
    for(int i = 0; i < prufer_count; i++) {
        cout << prufer[i] << " ";
    }

    // make vertex
    int vertex_list[vertex];
    for(int i = 0; i < vertex; i++) {
        vertex_list[i] = i + 1;
    }

    // make edges
    bool status = true;
    int edge[prufer_count + 1][2];
    for(int i = 0; i < prufer_count; i++) {
        for(int j = 0; j < vertex; j++) {
            if(prufer[i] != vertex_list[j]) {
                for(int k = 0; k < prufer_count; k++) {
                    if(vertex_list[j] == prufer[k]) {
                        status = false;
                        break;
                    }
                }
                if(status) {
                    edge[i][0] = prufer[i];
                    edge[i][1] = vertex_list[j];
                    prufer[i] = 0;
                    vertex_list[j] = 0;
                    break;
                }
                status = true;
            }
        }
    }

    // add last edge into edge array
    int insert = 0;
    for(int i = 0; i < vertex; i++) {
        if(insert > 1) break;
        if(vertex_list[i] != 0) {
            edge[prufer_count][insert] = vertex_list[i];
            vertex_list[i] = 0;
            insert++;
        }
    }

    // show tree edges
    cout << endl << endl << "Daftar edge graph pohon:" << endl;
    for(int i = 0; i < prufer_count + 1; i++) {
        cout << i + 1 << ". ";
        for(int j = 0; j < 2; j++) {
            cout << edge[i][j] << " ";
        }
        cout << endl;
    }

    return 0;

}