def checkSub(s, t, l, r, i):
    if l > r:
        return True

    if l == r and (s[l] == '?' or s[l] == t[i + l]):
        return True

    mid = (l + r) // 2
    if (s[l] == '?' or s[l] == t[i + l]) and (s[r] == '?' or s[r] == t[i + r]) \
        and (s[mid] == '?' or s[mid] == t[i + mid]):
        return checkSub(s, t, l + 1, mid - 1, i) and checkSub(s, t, mid + 1, r - 1, i)
    
    return False
    
def findMatches1(s, t):
    foundPositions = []

    m = len(s)
    n = len(t)

    i = 0
    
    while i <= n - m:
        l = 0
        r = m - 1

        if checkSub(s, t, l, r, i):
            foundPositions.append(i)
        i += 1

    return foundPositions

s = 'aaaab'
t = 'aaaaaaaaaaaabaaaaab'

print(findMatches1(s, t))