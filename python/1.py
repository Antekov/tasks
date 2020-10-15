# https://habr.com/ru/post/119158/
# https://lisiynos.github.io/s1/graph_alg_py.html

a, b, M, x, y = [int(c) for c in input().split()]

def G(start, end, M=M):
    if end == (start + 1) % M:
        return a
    elif end == (start * start + 1) % M:
        return b
    return 2000000000

INF = 2000000000
d = [INF] * M

start = [x]
d[x] = 0
for i in range(M):
    print(start)
    print(d)
    nex = set()
    for v in start:
        end = (v + 1) % M
        nex.add(end)
        if d[end] > d[v] + a:
            d[end] = d[v] + a

        end = (v * v + 1) % M
        nex.add(end)
        if d[end] > d[v] + a:
            d[end] = d[v] + a
    start = nex

print(d)
print(d[y])