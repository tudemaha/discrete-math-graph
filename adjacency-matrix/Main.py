import numpy as np

print('===== PROGRAM MATRIKS KETETANGGAAN =====')

matrix = []
nodes = int(input('\nBanyak node: '))

print('\nMasukkan 1 jika node terhubung, 0 jika tidak terhubung')

for row in range(nodes):
    matrix.append([])
    for column in range(nodes):
        matrix[row].append(int(input(f'Baris {row + 1}, Kolom {column + 1}: ')))

matrix = np.array(matrix)
print('\nMatriks ketetanggaan:')
print(matrix)