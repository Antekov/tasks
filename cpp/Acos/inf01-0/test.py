A = []
B = []

import numpy as np
import random

n = 4

for i in range(n):
    A.append([])
    B.append([])
    for j in range(n):
        A[i].append(random.random()*100)
        B[i].append(random.random()*100)
print(A)

print((np.array(A).dot(np.array(B))))

from matrix import dot

print(dot(n, A, B))