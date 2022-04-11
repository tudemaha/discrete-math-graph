import numpy as np

# program header
print("===== PROGRAM PEWARNAAN GRAPH =====")

# variable declaration for adjacency matrix
nodes = int(input("\nMasukkan banyak node: "))
matrix = []
matrix_info, deg = [], 0

# insert adjacency matrix
print("\nMasukkan 1 jika node terhubung, 0 jika tidak terhubung")
for row in range(nodes):
    matrix.append([])
    matrix_info.append({})
    matrix_info[row]["node"] = row + 1

    for column in range(nodes):
        matrix[row].append(int(input(f"Baris {row + 1}, Kolom {column + 1}: ")))
        deg += matrix[row][column]
    matrix_info[row]["derajat"] = deg
    deg = 0

# turn adjacency matrix into numpy matrix
matrix = np.array(matrix)

# show adjacency matrix
print("\nMatriks ketetanggan:")
for row in matrix:
    print(row)

# show deg info before sort
print("\nDerajat node sebelum sort:")
for dict in matrix_info:
    print(dict)

# selection sort for descending degrees
for i in range(len(matrix_info)):
    min_idx = i

    for j in range(i + 1, len(matrix_info)):
        if matrix_info[min_idx]["derajat"] < matrix_info[j]["derajat"]:
            min_idx = j
        
    matrix_info[i], matrix_info[min_idx] = matrix_info[min_idx], matrix_info[i]

# show deg info after sort
print("\nDerajat node setelah sort:")
for dict in matrix_info:
    print(dict)

# give color
warna, total = 1, 0
matrix_info[0]['warna'] = warna
kromatik = 0

tanda = matrix[(matrix_info[0]['node']) - 1, :]

for i in range(nodes):
    if total == nodes: 
        break
    for j in range(nodes):
        if (not("warna" in matrix_info[j])) and (tanda[(matrix_info[j]["node"]) - 1] == 0):
            matrix_info[j]["warna"] = warna
            total += 1
            kromatik = warna
            for k in range(nodes):
                if tanda[k] == 0:
                    tanda[k] = matrix[(matrix_info[j]["node"]) - 1][k]
    warna += 1
    for k in range(nodes):
        tanda[k] = 0

#selection sort for ascending node number
for i in range(len(matrix_info)):
    min_idx = i

    for j in range(i + 1, len(matrix_info)):
        if matrix_info[min_idx]["node"] > matrix_info[j]["node"]:
            min_idx = j
        
    matrix_info[i], matrix_info[min_idx] = matrix_info[min_idx], matrix_info[i]

# show color information
print("\nWarna Node:")
for dict in matrix_info:
    print(dict)

# bilangan kromatik
print("\nBilangan Kromatik: ", kromatik)