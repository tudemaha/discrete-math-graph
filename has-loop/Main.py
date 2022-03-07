# import library
import numpy as np

# program title
print('===== PROGRAM PENGECEKAN LOOP GRAPH =====')

# variables declaraion and initialization
nodes = int(input('\nBanyak node: '))
matrix = []

# insert adjacency matrix elements
print('\nMasukkan 1 jika node terhubung, 0 jika tidak terhubung')
for row in range(nodes):
    matrix.append([])
    for column in range(nodes):
        matrix[row].append(int(input(f'Baris {row + 1}, Kolom {column + 1}: ')))

# make matrix using numpy from user-inserted matrix
matrix = np.array(matrix)
# print the adjacency matrix
print('\nMatriks ketetanggaan')
print(matrix)

# create status var (false if there no loop)
status = False
# make 1D matrix from adjacency matrix's diagonal
diagonal = matrix.diagonal()
# check each element in diagonal to know if there are >=1 values (true if there are any loops)
for element in diagonal:
    if element > 0:
        status = True
        break

# print the loop status
print(('\nGraph tidak mengandung loop', '\nGraph mengandung loop!') [status == True])