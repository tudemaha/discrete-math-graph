import numpy as np
import sys

# cycle detection, parameter: vertices and latest testing matrix
def cycle_check(vertices, matrix_test):
    flag = []                       # store vertices flag
    queue = []                      # queue for bfs method
    visited = []                    # store visited and not make cycle
    cycle_maker = []                # store vertices that make cycle
    pop_state = 0                   # index to pop queue
    matrix = np.copy(matrix_test)   # copy matrix test so the function not change the matrix input

    # make i index to store vertices flag
    for i in range(vertices):
        flag.append(-1)

    # bfs cycle detection
    for i in range(vertices):
        if flag[i] == -1:       # if vertex i flag is -1
            queue.append(i)     # push i into queue
            flag[i] += 1        # add 1 in vertex i flag
        
        if(flag[i] == 0) and (i not in cycle_maker):    # if vertex i flag is 0 and i not in the cycle maker
            visited.append(queue.pop(pop_state))        # pop i from queue and push into visited list
            flag[i] += 1                                # add 1 in vertex i flag

            # iterate column j in row i to know neighbor vertex
            for j in range(vertices):
                if(matrix[i][j] == 1) and (flag[j] == -1):  # if there is a neighbor in matrix[i][j] and it's flag -1
                    queue.append(j)                         # push j into queue
                    matrix[i][j] = matrix[j][i] = 0         # make the neighbor vertices 0
                    flag[j] += 1                            # add 1 in vertex j flag
                elif(matrix[i][j] == 1) and (flag[j] == 0):     # if there is a neighbor in matrix[i][j] and it's flag 0
                    cycle_maker.append(j)                       # j is the cycle maker, so push it into cycle_maker list
        elif(flag[i] == 0) and (i in cycle_maker):      # if vertex i flag is 0 and i in the cycle maker
            pop_state += 1                              # add 1 to pop_state to skip popping vetex i

    # print for debugging
    # print(flag)
    # print(matrix_test)

    # if there 0 in flag list, return true to inform that is a cycle in the graph
    if 0 in flag:
        return True
    else:
        return False

# check for connected graph
def connected(matrix):
    helper_matrix = np.copy(matrix[0, :])
    for row in range(len(matrix)):
        if helper_matrix[row] == 1:
            for column in range(len(matrix)):
                if(matrix[row][column] == 1) and (helper_matrix[column] == 0):
                    helper_matrix[column] = 1

    if 0 in helper_matrix:
        return False
    else:
        return True

matrix = []         # adjacency matrix from user insert
sorted_edge = []    # store ascending sorted edge weight of graph
mst = []            # store the minimum spanning tree graph
graph_weight = 0    # store mst edge weight

# open matrix file and insert into matrix list
matrix_file = open("edge_weight.txt")
for line in matrix_file:
    matrix.append(line.split())
matrix_file.close()

# change matrix element from string to int
for i, row in enumerate(matrix):
    matrix[i] = list(map(int, matrix[i]))
matrix = np.array(matrix)

# check for connected graph
connect = connected(matrix)
if not connect:
    sys.exit("Graph tidak terhubung, proses tidak dapat dilanjutkan!")

# count vertices
vertices = len(matrix)

# make an empty adjacency matrix for mst
for i in range(vertices):
    mst.append([])
    for j in range(vertices):
        mst[i].append(0)
mst = np.array(mst)

# insert row, column, and edge weight into sorted_edge list (diagonal way)
for i in range(vertices):
    for j in range(i, vertices):
        if matrix[i][j] != 0:
            sorted_edge.append([i, j, matrix[i][j]])

# sort edge in ascending mode using selection sort
for i in range(len(sorted_edge)):
    min_idx = i
    
    for j in range(i + 1, len(sorted_edge)):
        if sorted_edge[i][2] > sorted_edge[j][2]:
            min_idx = j
    sorted_edge[i], sorted_edge[min_idx] = sorted_edge[min_idx], sorted_edge[i]

# print edge-weight matrix
print("Graph awal:")
print(matrix)

# make adjacency matrix from sorted edge and check for the cycle
print("\nEdge terhubung:")
for i in range(len(sorted_edge)):
    # mst[m][n] = mst[n][m] because it's undirected graph, if there was an edge in sorted_edge list, make the vertices 1
    mst[sorted_edge[i][0]][sorted_edge[i][1]] = mst[sorted_edge[i][1]][sorted_edge[i][0]] = 1
    
    # cycle detection from adjacency matrix made before
    status = cycle_check(vertices, mst)
    # if the return status is true (there is a cycle), make the vertices 0 again (skip inserting the current edge)
    if status:
        mst[sorted_edge[i][0]][sorted_edge[i][1]] = mst[sorted_edge[i][1]][sorted_edge[i][0]] = 0
        continue
    
    graph_weight += sorted_edge[i][2]
    print(sorted_edge[i][0], "-", sorted_edge[i][1])

# print for debugging
# print(matrix, end="\n\n")
# print(sorted_edge, end="\n\n")

# print the mst adjacency matrix and it's the minimum spanning tree
print("\nMinimum Spanning Tree:")
print(mst)

# print mst weight
print("\nBobot graph: ", graph_weight)