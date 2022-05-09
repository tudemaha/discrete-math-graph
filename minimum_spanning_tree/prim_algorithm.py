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


# preparing empty list for
matrix = []     # store adjacency matrix
mst = []        # mst adjacency matrix
edges = []      # list of weighted edges
mst_weight = 0  # store mst weight

# open matrix adjacency file and store in matrix list
matrix_file = open("graph.txt")
for row in matrix_file:
    matrix.append(row.split())

# count for vertices
vertices = len(matrix)

# convert string to int in matrix list
for i in range(vertices):
    matrix[i] = list(map(int, matrix[i]))
matrix = np.array(matrix)

# check for connected graph, exit if graph not connected
if not connected_graph(matrix):
    sys.exit("Graph tidak terhubung, proses tidak dapat dilanjutkan!")

# count for edges weight and its vertices and store in edges list
for i in range(vertices):
    for j in range(i, vertices):
        if matrix[i][j] != 0:
            edges.append({"from": i, "to": j, "weight": matrix[i][j]})

# make an empty mst adjacency matrix based on n x n elements
for i in range(vertices):
    mst.append([])
    for j in range(vertices):
        mst[i].append(0)

# print adjacency matrix
print("Matriks ketetanggan awal:")
print(matrix, end="\n\n")

# search first edge with minimum weight
print("Prim's MST Edges:")
# consider the first set in edge list is the minimum edge
minimal = edges[0]
# search for the minimum one, if there was replace the minimal before
for i in range(len(edges)):
    if minimal["weight"] > edges[i]["weight"]:
        minimal = edges[i]
# insert the vertices of minimum edge into mst
mst[minimal["from"]][minimal["to"]] = mst[minimal["to"]][minimal["from"]] = minimal["weight"]
print(f"{minimal['from']}-{minimal['to']} -> {minimal['weight']}")
# sum for the weight
mst_weight += minimal['weight']
# remove the minimal (selected) edge
edges.remove(minimal)

# next vertices
# prepare selected edge before
edge_before = []
while edges != []:
    # store the minimum before into edge before
    for vertex in ["from", "to"]:
        edge_before.append(minimal[vertex])

    # consider the first set in edge list is the minimum edge
    minimal = edges[0]
    # search for the actual minimum edges
    for i in range(len(edges)):
        if minimal["weight"] > edges[i]["weight"]:
            minimal = edges[i]
    
    # if the current minimal edge weight is in edge before
    if (minimal["from"] in edge_before) or (minimal["to"] in edge_before):
        # add the vertices from the minimal edge into mst
        mst[minimal["from"]][minimal["to"]] = mst[minimal["to"]][minimal["from"]] = minimal["weight"]

        # check for the cycle
        status = cycle_detection(vertices, mst)
        # if the selected minimum edge makes cycle
        if status:
            # make the current vertices 0 again, else print the vertices and sum weight
            mst[minimal["from"]][minimal["to"]] = mst[minimal["to"]][minimal["from"]] = 0
        else:
            print(f"{minimal['from']}-{minimal['to']} -> {minimal['weight']}")
            mst_weight += minimal['weight']
        
        # remove selected edge
        edges.remove(minimal)

# print the edge information
print("\nPrim's MST:")
mst = np.array(mst)
print(mst, end="\n\n")

print("Bobot graph:", mst_weight)