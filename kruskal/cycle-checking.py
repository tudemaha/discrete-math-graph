from itertools import cycle
import numpy as np
from pymacaroons import Verifier

matrix = [
    [0, 1, 1, 0, 0],
    [1, 0, 0, 1, 1],
    [1, 0, 0, 0, 0],
    [0, 1, 0, 0, 0],
    [0, 1, 0, 0, 0]
]
matrix = np.array(matrix)

flag = [-1, -1, -1, -1, -1]
queue = []
visited = []
vertices = len(matrix)
cycle_maker = []

for i in range(vertices):
    if flag[i] == -1:
        queue.append(i)
        flag[i] += 1
    
    if (flag[i] == 0) and (i not in cycle_maker):
        visited.append(queue.pop(0))
        flag[i] += 1

        for j in range(vertices):
            if (matrix[i][j] == 1) and (flag[j] == -1):
                queue.append(j)
                flag[j] += 1
            elif(matrix[i][j] == 1) and (flag[j] == 0):
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
else:
    print("Status: Graph tidak mengandung cycle!")