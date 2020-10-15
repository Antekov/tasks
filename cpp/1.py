def f(n, s = 1, level=0):
    print('  '*level + f'f({s}, {n})')
    if n < s:
        return 0

    if n == s:
        return n*(n + 1)

    return f(s + (n-s)//2, s, level+1) + f(n, s + (n-s)//2 + 1, level+1)


f(10)