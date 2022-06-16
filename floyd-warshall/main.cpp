#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream matrix;
    int vertices;
    
    matrix.open("graph.txt");
    int buffer;
    while(!matrix.eof()) {
        matrix >> buffer;
        vertices++;
    }
    matrix.close();

    int graph[vertices][vertices];

    matrix.open("graph.txt");
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            matrix >> graph[vertices][vertices];
        } 
    }
    matrix.close();

    cout << vertices;

    return 0;
}