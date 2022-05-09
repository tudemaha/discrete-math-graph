void cycle_detection(int vertices, std::array<std::array<int, 2>, 2> matrix) {
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}