bool cycle_detection(int vertices, int **mst_test) {
    int flag[vertices];
    int matrix[vertices][vertices];
    std::vector<int> cycle_maker;

    for(int i = 0; i < vertices; i++) {
        flag[i] = 0;
    }

    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            matrix[i][j] = mst_test[i][j];
        }
    }

    bool cycle_status = false;
    for(int i = 0; i < vertices; i++) {
        if(flag[i] == 0) flag[i] = 1;

        for(int x = 0; x < cycle_maker.size(); x++) {
            if(i == cycle_maker[x]) cycle_status = true;
        }

        if((flag[i] == 1) and (!cycle_status)) {
            for(int j = 0; j < vertices; j++) {
                if((matrix[i][j] != 0) and (flag[j] == 0)) {
                    matrix[i][j] = matrix[j][i] = 0;
                    flag[j] = 1;
                } else if((matrix[i][j] != 0) and (flag[j] == 1)) {
                    cycle_maker.push_back(j);
                }
            }
        }
    }

    if(cycle_maker.empty()) return false;
    else return true;
}

bool connected_graph(int vertices, int **matrix) {
    int helper_matrix[vertices];
    
    for(int i = 0; i < vertices; i++) {
        helper_matrix[i] = matrix[0][i];
    }

    for(int i = 0; i < vertices; i++) {
        if(helper_matrix[i] != 0) {
            for(int j = 0; j < vertices; j++) {
                if((matrix[i][j] > 0) and (helper_matrix[j] == 0)) {
                    helper_matrix[j] = 1;
                }
            }
        }
    }

    for(int i = 0; i < vertices; i++) {
        if(helper_matrix[i] == 0) return false;
    }
    
    return true;
}

bool neighbor_checking(std::vector<int> &set_of_vertices, int vertex) {
    for(int i = 0; i < set_of_vertices.size(); i++) {
        if(vertex == set_of_vertices[i]) return true;
    }
    return false;
}