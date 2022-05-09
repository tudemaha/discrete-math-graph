// import libraries
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;

int main() {
    // prepare for file reading opreation
    ifstream matrix_file;

    // count all adjacency matrix elements
    matrix_file.open("graph.txt");
    int vertices = 0, buffer;
    while(!matrix_file.eof()) {
        matrix_file >> buffer;
        vertices++;
    }
    matrix_file.close();

    // count vertices
    vertices = sqrt(vertices);
    // make adjacency matrix array
    int matrix[vertices][vertices];

    // fill all adjacency matrix array from matrix_file
    matrix_file.open("graph.txt");
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            matrix_file >> matrix[i][j];
        }
    }

    // print adjacency matrix
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // make array of flag for each vertices (0 unvisited, 1 visited)
    int flag[vertices];
    // make a vector to vertices that make cycle(s)
    vector<int> cycle_maker;
    // fill all flag with 0
    for(int i = 0; i < vertices; i++) {
        flag[i] = 0;
    }

    // status to check if an vertices make a cycle or no
    bool status;
    for(int i = 0; i < vertices; i++) {
        // if the current vertex unvisited, make it visited
        if(flag[i] == 0) flag[i] = 1;

        // check for the current vertex status (make cycle or no)
        for(int x = 0; x < cycle_maker.size(); x++) {
            if(i == cycle_maker[x]) status = true;
        }

        // if the current vertex is visited and not make cycle(s)
        if((flag[i] == 1) and (!status)) {
            // loop all the column of current row
            for(int j = 0; j < vertices; j++) {
                // if the neighbor vertex (j) is 1 and j flag's is 0
                if((matrix[i][j] == 1) and flag[j] == 0) {
                    // if there is a neighbor vertex (j) and j flag's is 0
                    matrix[i][j] = matrix[j][i] = 0;
                    // set the neighbor vertex flag's 1
                    flag[j] = 1;
                    // if there is a neighbor vertex (j) and j flag's is 1
                } else if((matrix[i][j] == 1) and flag[j] == 1) {
                    // it's the cycle maker, so push it into cycle_maker
                    cycle_maker.push_back(j);
                }
            }
        }
    }

    
    // print the cycle detection status
    if(cycle_maker.empty()) {
        cout << "Graph tidak memiliki cycle." << endl;
    } else {
        cout << "Grap memiliki cycle." << endl;
    }

    return 0;
}