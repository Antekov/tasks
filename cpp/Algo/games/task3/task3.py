n = int(input())

V = dict()

V[(0,0)] = set()
V[(0,1)] = set()
V[(1,1)] = set()
V[(0,2)] = set([(0,1)])

for k in range(n):
    for i in range(2, n+1-k):
        V[(k,i)] = {tuple(sorted([k, i-1])), tuple(sorted([k, i-2]))}
        for j in range(i-1, i-1):
            V[(k,i)].add(tuple(sorted([j-1, i-j])))

for prev, nexts in V.items():
    print(prev, ':', *nexts)


N = set()

for prev, nexts in V.items():
    print(prev, ':', *nexts)
    c = 0
    for pos in nexts:
        if len(V[pos]) == 0:
            N.add(prev)
            c += 1
    

