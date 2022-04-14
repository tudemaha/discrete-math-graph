import numpy as np

matrix = []

# add adjacency matrix from file into matrix list
matrix_file = open("adjacency-matrix.txt")
for line in matrix_file:
    matrix.append(line.split())
matrix_file.close()

# convert every element on matrix list to int
for i, row in enumerate(matrix):
    matrix[i] = list(map(int, matrix[i]))
matrix = np.array(matrix)

# count vertices
vertices = len(matrix)

# connected graph check
helper_matrix = matrix[0].copy()
for row in range(vertices):
    if helper_matrix[row] == 1:
        for column in range(vertices):
            if (matrix[row][column] == 1) and (helper_matrix[column] == 0):
                helper_matrix[column] = 1

for row in helper_matrix:
    if row == 0:
        print("Graph tidak terhubung, proses tidak dapat dilanjutkan!")
        exit()

# hamilton cycle
hamilton = []
for i in range(vertices):
    hamilton.append(0)

while True:
    for i in range(vertices):
        hamilton[i] = 0

        for j in range(vertices):
            if matrix[hamilton[i]][j] == 1:
                temp = j
                break
        hamilton[i + 1] = temp


    





print(matrix)
print(helper_matrix)