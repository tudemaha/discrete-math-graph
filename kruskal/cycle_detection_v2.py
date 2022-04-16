import numpy as np

matrix = [
    [0, 1, 1, 0, 0],
    [1, 0, 0, 1, 1],
    [1, 0, 0, 0, 0],
    [0, 1, 0, 0, 0],
    [0, 1, 0, 0, 0]
]
matrix = np.array(matrix)

flag = [0, 0, 0, 0, 0]
queue = []
visited = []
vertices = len(matrix)
status = False

edge = 0
while edge < vertices:
    for i in range(vertices):
        if flag[i] == 0:
            queue.append(i)
            flag[i] += 1

        for j in range(vertices):
            if (matrix[i][j] == 1) and (flag[j] == 0):
                status = True
                queue.append(j)
                flag[j] += 1
                matrix[i][j] = matrix[j][i] = 0
        
        if (i in queue) and (flag[i] == 1) and status:
            visited.append(queue.pop(queue.index(i)))
            edge += 1
            status = False
            break

        if status == False:
            edge += 1
            break

print(flag)
print(queue)
print(visited)
print(matrix)