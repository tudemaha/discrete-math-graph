#include <iostream>
#include <fstream>

using namespace std;

int main() {
    cout << "===== PRUFER DECODE =====" << endl;
    cout << "=========================" << endl << endl;

    int buffer, count = 0;

    ifstream prufer_file;

    // count length of prufer code
    prufer_file.open("prufer-code.txt");
    while(!prufer_file.eof()) {
        prufer_file >> buffer;
        count++;
    }
    prufer_file.close();

    // add prufer code into array
    prufer_file.open("prufer-code.txt");
    int prufer[count];
    for(int i = 0; i < count; i++) {
        prufer_file >> prufer[i];
    }
    prufer_file.close();

    // show prufer code
    cout << "Kode prufer: ";
    for(int i = 0; i < count; i++) {
        cout << prufer[i] << " ";
    }

    // make vertex
    int vertex[count + 2];
    for(int i = 0; i < count + 2; i++) {
        vertex[i] = i + 1;
    }

    // make edges
    bool status = true;
    int edge[count + 1][2];
    for(int i = 0; i < count; i++) {
        for(int j = 0; j < count + 2; j++) {
            if(prufer[i] != vertex[j]) {
                for(int k = 0; k < count; k++) {
                    if(vertex[j] == prufer[k]) {
                        status = false;
                        break;
                    }
                }
                if(status) {
                    edge[i][0] = prufer[i];
                    edge[i][1] = vertex[j];
                    prufer[i] = 0;
                    vertex[j] = 0;
                    break;
                }
                status = true;
            }
        }
    }

    // add last edge into edge array
    int insert = 0;
    for(int i = 0; i < count + 2; i++) {
        if(insert > 1) break;
        if(vertex[i] != 0) {
            edge[count][insert] = vertex[i];
            vertex[i] = 0;
            insert++;
        }
    }

    // show tree edges
    cout << endl << endl << "Daftar edge graph pohon:" << endl;
    for(int i = 0; i < count + 1; i++) {
        cout << i + 1 << ". ";
        for(int j = 0; j < 2; j++) {
            cout << edge[i][j] << " ";
        }
        cout << endl;
    }
}