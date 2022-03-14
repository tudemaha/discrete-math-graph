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

# check the direction status of adjacency matrix (False == has no directed)
status = False

# check the symetrical elements is same ([row][column] == [column][row])
for row in range(nodes):
    for column in range(nodes):
        if matrix[row][column] != matrix[column][row]:
            status = True
            row = nodes + 1
            break

x, deg, in_deg, out_deg = 0, 0, 0, 0
deg_list = []
print("\nDerajat graph:")
if status == False:
    for row in matrix:
        for element in row:
            deg += element
        x += 1
        print("Node", x, ":", deg)
        deg = 0

else:
    for node in range(nodes):
        deg_list.append({})
        deg_list[node]["node"] = node + 1
        for element in matrix[node, :]:
            out_deg += element
            deg_list[node]["out_deg"] = out_deg
            out_deg = 0
        for element in matrix[:, node]:
            in_deg += element
            deg_list[node]["in_deg"] = in_deg
            in_deg = 0

for dict in deg_list:
    print(dict)