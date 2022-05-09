# import numpy to make an array
from itertools import cycle
import numpy as np

# variables to store:
matrix = []         # adjacency matrix (matrix)
visited = []        # visited vertices (visited)
cycle_maker = []    # vertices that make cycle (cycle maker)

# open matrix file and insert into matrix list
matrix_file = open("graph.txt")
for line in matrix_file:
    matrix.append(line.split())
matrix_file.close()

# count vertices
vertices = len(matrix)

# convert matrix list from string to int
for i in range(vertices):
    matrix[i] = list(map(int, matrix[i]))

# make a numpy matrix
matrix = np.array(matrix)

# print adjacency matrix
print("Matriks ketetanggaan:")
print(matrix)

# vertices status for each vertices
flag = []
for i in range(vertices):
    flag.append(0)

for i in range(vertices):
    if flag[i] == 0:
        visited.append(i)
        flag[i] = 1

    if(flag[i] == 1) and (i not in cycle_maker):
        for j in range(vertices):
            if(matrix[i][j] == 1) and (flag[j] == 0):
                visited.append(j)
                matrix[i][j] = matrix[j][i] = 0
                flag[j] = 1
            elif(matrix[i][j] == 1) and (flag[j] == 1):
                cycle_maker.append(j)

# print cycle detection status
print("\nStatus:")
if cycle_maker != []:
    print("Graph memiliki cycle.")
else:
    print("Graph tidak memiliki cycle.")