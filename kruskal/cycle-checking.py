from itertools import cycle
import numpy as np

matrix = [
    [0, 1, 1, 0, 0, 0],
    [1, 0, 0, 1, 1, 1],
    [1, 0, 0, 1, 0, 0],
    [0, 1, 1, 0, 0, 0],
    [0, 1, 0, 0, 0, 0],
    [0, 1, 0, 0, 0, 0]
]
matrix = np.array(matrix)

flag = [-1, -1, -1, -1, -1, -1]
queue = []
visited = []
vertices = len(matrix)
cycle_maker = []

for i in range(vertices):
    if i in cycle_maker:
        continue

    if flag[i] == -1:
        queue.append(i)
        flag[i] += 1

    if (i in queue) and (flag[i] == 0):
        visited.append(queue.pop(queue.index(i)))
        flag[i] += 1
                    
        for j in range(vertices):
            if (matrix[i][j] == 1) and (flag[j] == -1):
                status = 1
                queue.append(j)
                flag[j] += 1
                matrix[i][j] = matrix[j][i] = 0

            if (matrix[i][j] == 1) and (flag[j] == 0):
                cycle_maker.append(j)

print("Status tiap vertex:")
print(flag, end="\n\n")

print("Keadaan queue:")
print(queue, end="\n\n")

print("Graph tanpa cycle:")
print(visited, end="\n\n")

print("Matriks ketetangaan akhir:")
print(matrix, end="\n\n")

if 0 in flag:
    print("Status: Graph mengandung cycle!")