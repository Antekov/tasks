ping = ['   _~_   ', '  (o o)  ', ' /  V  \\ ',
        '/(  _  )\\', '  ^^ ^^  ']

n = int(input())

for s in ping:
    for i in range(n):
        print(s, end=' ')
    print()
