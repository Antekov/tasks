s = input()
t = input()

parts = s.split('?')
print(parts)

aut = []

part = ''
k = 0
p = ''
m = len(s)
aut.append(s[0])

for i in range(1, m):
    if s[i] != '?' and s[i-1] != '?':
        aut[k] += s[i]
    elif s[i] == '?' and s[i - 1] == '?':
        aut[k] += s[i]
    else:
        aut.append(s[i])
        k += 1

print(aut)

n = len(t)
k = len(aut)

i = 0
partNum = 0
partPos = 0
matchLen = 0
foundPositions = []
while i < n:
    partLen = len(aut[partNum])
    if aut[partNum][0] == '?':
        i += partLen
        matchLen += partLen
        if i > n:
            break
        partNum += 1
        if partNum == k:
            foundPositions.append(i - m)
            partNum = 0
            partPos = 0
            matchLen = 0
        continue
    if aut[partNum][partPos] == t[i]:
        i += 1
        matchLen += 1
        partPos += 1
        if partPos == partLen:
            partPos = 0
            partNum += 1
        if partNum == k:
            foundPositions.append(i - m)
            partNum = 0
        continue
    if aut[partNum][partPos] != t[i]:
        i += 1
        if i >= n:
            break
        i -= matchLen
        partNum = 0
        partPos = 0
        matchLen = 0

print(*foundPositions)
    