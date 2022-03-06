# import library
import numpy as np

# program title
print('===== PROGRAM MATRIKS KETETANGGAAN =====')

# variable declaration and initialization
matrix = []
nodes = int(input('\nBanyak node: '))

# show instructions
print('\nMasukkan 1 jika node terhubung, 0 jika tidak terhubung')

# insert adjacency matrix elements
for row in range(nodes):
    matrix.append([])
    for column in range(nodes):
        matrix[row].append(int(input(f'Baris {row + 1}, Kolom {column + 1}: ')))

# make matrix using numpy
matrix = np.array(matrix)

# show adjacency matrix
print('\nMatriks ketetanggaan:')
print(matrix)