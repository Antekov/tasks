def mex(s) -> int:
    if -1 in s:
        return -1
    x = 0
    while x in s:
        x += 1
    return x

n = int(input())

g = [0]*max(8, (n+1))

g[0] = mex(set())
g[1] = mex(set())

w = []

m = 2
while m <= n:
    s = set()

    for i in range(1, (m + m % 2) // 2 + 1):
        xor = g[i - 1] ^ g[m - i]
        s.add(xor)
        if m == n and xor == 0:
            w.append(i)
            w.append(n-i+1)

    g[m] = mex(s)
    m += 1

# print(g)


if g[n] > 0:
    print('Schtirlitz')
else:
    print('Mueller')

print(*sorted(set(w)), sep='\n')
