# import library
import numpy as np

# program title
print('===== PROGRAM KETERHUBUNGAN GRAPH =====')

# variables declaration and initialization
nodes = int(input('\nBanyak node: '))
matrix = []

# insert adjacency matrix elements
print('\nMasukkan 1 jika node terhubung, 0 jika tidak terhubung')
for row in range(nodes):
    matrix.append([])
    for column in range(nodes):
        matrix[row].append(int(input(f'Baris {row + 1}, Kolom {column + 1}: ')))

# make adjacency matrix using numpy
matrix = np.array(matrix)
# make helper matrix by slicing the adjacency matrix at row 1 from column 2 to end 
helper_matrix = matrix[0, 1:]

# show first state of matrices
print('\nMatriks ketetanggaan:')
print(matrix)
print('\nMatriks bantuan awal:')
print(helper_matrix)

# check for the connection of graph in adjacency matrix
for row in range(nodes - 1):
    if helper_matrix[row] == 1:
        for column in range(nodes - 1):
            if (matrix[row + 1][column + 1] == 1) and (helper_matrix[column] == 0):
                helper_matrix[column] = 1

# show last state of matrices
print('\nMatriks bantuan akhir:')
print(helper_matrix)

# check the connection in helper matrix (True == connected)
status = True
for helper in helper_matrix:
    if helper == 0:
        status = False
        break

# print the connection status
print(("Graph tidak terhubung!", "Graph terhubung") [status == True])