n = int(input("Enter number of processes: "))
m = int(input("Enter number of resources: "))

avail = list(map(int, input("Enter available resources: ").split()))

print("\nEnter Allocation Matrix:")
alloc = []
for i in range(n):
    row = list(map(int, input(f"Process {i+1}: ").split()))
    alloc.append(row)

print("\nEnter Max Matrix:")
max_matrix = []
for i in range(n):
    row = list(map(int, input(f"Process {i+1}: ").split()))
    max_matrix.append(row)

need = []
for i in range(n):
    row = []
    for j in range(m):
        row.append(max_matrix[i][j] - alloc[i][j])
    need.append(row)

finish = [False] * n
count = 0

while count < n:
    allocated = False
    
    for i in range(n):
        if not finish[i]:
            possible = True
            
            for j in range(m):
                if need[i][j] > avail[j]:
                    possible = False
                    break
            
            if possible:
                for j in range(m):
                    avail[j] += alloc[i][j]
                
                finish[i] = True
                count += 1
                allocated = True
    
    if not allocated:
        break


if count == n:
    print("\nSystem is in SAFE state.")
else:
    print("\nSystem is NOT in safe state.")

