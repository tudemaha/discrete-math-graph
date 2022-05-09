# import libraries
import numpy as np
import sys

# function to test connected graph in kruskal's algorithm
def cycle_detection(vertices, mst_test):
    # prepaing variables for:
    matrix = np.copy(mst_test)  # copy of current mst from parameter
    visited = []                # visited vertices set
    cycle_maker = []            # vertices that make cycle
    flag = []                   # flag for each vertices (visited or no)

    # make all flag 0
    for i in range(vertices):
        flag.append(0)

    # cycle detection
    for i in range(vertices):
        # if current flag is 0 and visiting it, append vertex into visited set, and turn flag to 1
        if flag[i] == 0:
            visited.append(i)
            flag[i] = 1

        # if current flag is 1 and not in cycle_maker set, check for its neightbor
        if(flag[i] == 1) and (flag[i] not in cycle_maker):
            for j in range(vertices):
                # if matrix[i][j] (neighbor vertex) greater than 0 and its flag is 0
                # append neighbor vertex into visited set, turn matrix[i][j] and matrix[j][i] to 0
                # and set the neigbor flag to 1
                if(matrix[i][j] > 0) and (flag[j] == 0):
                    visited.append(j)
                    matrix[i][j] = matrix[j][i] = 0
                    flag[j] = 1
                # if matrix[i][j] (neighbor vertex) greater than 0 and its flag is 1
                # append the neighbor vertex into cycle_maker set
                elif(matrix[i][j] > 0) and (flag[j] == 1):
                    cycle_maker.append(j)
    
    # if there are some cycle maker, return true, else return false
    if cycle_maker != []:
        return True
    else:
        return False
            
# function to check connected graph
def connected_graph(matrix):
    # copy first adjacency matrix row to helper_matrix
    helper_matrix = np.copy(matrix[0, :])

    # do loop for each row
    for row in range(len(matrix)):
        # if current helper matrix not 0
        if helper_matrix[row] != 0:
            # do loop for each columnn
            for column in range(len(matrix)):
                # if current row and column greater than 0 and helper_matrix[column] still 0
                if(matrix[row][column] > 0) and (helper_matrix[column] == 0):
                    # change helper_matrix[column] to 1
                    helper_matrix[column] = 1

    # if 0 in helper matrix (graph not connected) return false, else return true
    if 0 in helper_matrix:
        return False
    else:
        return True

# make empty list to store:
matrix = []         # adjacency matrix
sorted_edge = []    # sorted edge weight
mst = []            # empty mst adjacency matrix
mst_weight = 0      # mst weight

# store adjacency matrix from file into matrix_file
matrix_file = open("graph.txt")
for line in matrix_file:
    matrix.append(line.split())

# count vertices
vertices = len(matrix)

# map stored adjacency matrix from string to int
for i in range(vertices):
    matrix[i] = list(map(int, matrix[i]))

# make a numpy array from adjacency matrix
matrix = np.array(matrix)

# checking for connected graph
connected = connected_graph(matrix)
# if graph not connected, stop the process
if not connected:
    sys.exit("Graph tidak terhubung, proses tidak dapat dilanjutkan!")

# print adjacency matrix
print("Matriks ketetanggaan awal:")
print(matrix, end="\n\n")

# store edges weight with their vertices
for i in range(vertices):
    for j in range(i, vertices):
        if matrix[i][j] != 0:
            sorted_edge.append({"from": i, "to": j, "weight": matrix[i][j]})

# sort edge from the minimum (selection sort)
for i in range(len(sorted_edge)):
    min_idx = i
    for j in range(i + 1, len(sorted_edge)):
        if sorted_edge[i]["weight"] > sorted_edge[j]["weight"]:
            min_idx = j
    sorted_edge[i], sorted_edge[min_idx] = sorted_edge[min_idx], sorted_edge[i]

# prepare empty mst adjacency matrix
for i in range(vertices):
    mst.append([])
    for j in range(vertices):
        mst[i].append(0)

# make the mst adjacency matrix using kruskal's algorithm
print("MST Edges:")
for i in range(len(sorted_edge)):
    # set mst from current sorted_edge 'from' and 'to' with their weight
    # cause that the undirected graph, mst[m][n] == mst[n][m]
    mst[sorted_edge[i]["from"]][sorted_edge[i]["to"]] = mst[sorted_edge[i]["to"]][sorted_edge[i]["from"]] = matrix[sorted_edge[i]["from"]][sorted_edge[i]["to"]]

    # check for cycle using cycle_detection function
    status = cycle_detection(vertices, mst)
    if status:
        # if there was a cycle, turn the current vertices back to 0 and continue
        mst[sorted_edge[i]["from"]][sorted_edge[i]["to"]] = mst[sorted_edge[i]["to"]][sorted_edge[i]["from"]] = 0
        continue

    # sum mst weight
    mst_weight += sorted_edge[i]["weight"]
    print(f"{sorted_edge[i]['from']}-{sorted_edge[i]['to']} -> {sorted_edge[i]['weight']}")


# print MST information
print("\nKruskal MST:")
mst = np.array(mst)
print(mst, end="\n\n")

print(f"Bobot MST: {mst_weight}")