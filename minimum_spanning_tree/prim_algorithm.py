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


matrix = []
mst = []
edges = []
mst_weight = 0

matrix_file = open("graph.txt")
for row in matrix_file:
    matrix.append(row.split())

vertices = len(matrix)

for i in range(vertices):
    matrix[i] = list(map(int, matrix[i]))
matrix = np.array(matrix)

if not connected_graph(matrix):
    sys.exit("Graph tidak terhubung, proses tidak dapat dilanjutkan!")

for i in range(vertices):
    for j in range(i, vertices):
        if matrix[i][j] != 0:
            edges.append({"from": i, "to": j, "weight": matrix[i][j]})

for i in range(vertices):
    mst.append([])
    for j in range(vertices):
        mst[i].append(0)

print("Matriks ketetanggan awal:")
print(matrix, end="\n\n")

# two first used vertices
print("Prim's MST Edges:")
minimal = edges[0]
for i in range(len(edges)):
    if minimal["weight"] > edges[i]["weight"]:
        minimal = edges[i]
mst[minimal["from"]][minimal["to"]] = mst[minimal["to"]][minimal["from"]] = minimal["weight"]
print(f"{minimal['from']}-{minimal['to']} -> {minimal['weight']}")
mst_weight += minimal['weight']
edges.remove(minimal)

# next vertices
sebelumnya = []
while edges != []:
    for vertex in ["from", "to"]:
        sebelumnya.append(minimal[vertex])

    minimal = edges[0]
    for i in range(len(edges)):
        if minimal["weight"] > edges[i]["weight"]:
            minimal = edges[i]
        
    if (minimal["from"] in sebelumnya) or (minimal["to"] in sebelumnya):
        mst[minimal["from"]][minimal["to"]] = mst[minimal["to"]][minimal["from"]] = minimal["weight"]

        status = cycle_detection(vertices, mst)
        if status:
            mst[minimal["from"]][minimal["to"]] = mst[minimal["to"]][minimal["from"]] = 0
        else:
            print(f"{minimal['from']}-{minimal['to']} -> {minimal['weight']}")
            mst_weight += minimal['weight']
        
        edges.remove(minimal)

print("\nPrim's MST:")
mst = np.array(mst)
print(mst, end="\n\n")

print("Bobot graph:", mst_weight)


    
    
