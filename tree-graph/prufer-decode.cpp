#include <iostream>
#include <fstream>

using namespace std;

int main() {
    cout << "===== PRUFER DECODE =====" << endl;
    cout << "=========================" << endl << endl;

    int buffer, count = 0;

    ifstream prufer_file;

    // count length of prufer code
    prufer_file.open("prufer-file.txt");
    while(!prufer_file.eof()) {
        prufer_file >> buffer;
        count++;
    }
    prufer_file.close();

    // add prufer code into array
    prufer_file.open("prufer-file.txt");
    int prufer[count];
    for(int i = 0; i < count; i++) {
        prufer_file >> prufer[i];
    }
    prufer_file.close();

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
                    if(vertex[j] == prufer[k]) status = false;
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

    for(int i = 0; i < count; i++) {
        cout << prufer[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < count + 2; i++) {
        cout << vertex[i] << " ";
    }

    return 0;
}