# import library
import numpy as np

# program title
print('===== PROGRAM PENGECEKAN ARAH GRAPH =====')

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

# check the direction status of adjacency matrix (False == not connected)
status = False

# check the symetrical elements is same ([row][column] == [column][row])
for row in range(nodes):
    for column in range(nodes):
        if matrix[row][column] != matrix[column][row]:
            status = True
            row = nodes + 1
            break

# show the direction status
print(("\nGraph tidak berarah!", "\nGraph berarah!") [status == True])