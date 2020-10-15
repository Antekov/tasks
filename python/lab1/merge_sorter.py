from heapq import heappush, heappop


def merge_sorter(*iterables):
    h = []

    iters = []
    i = 0

    for it in iterables:
        try:
            iterator = iter(it)
            el = next(iterator)
            iters.append(iterator)
            heappush(h, (el, i))
            i += 1
        except Exception:
            pass

    while True:
        try:
            el = heappop(h)
        except Exception:
            break

        i = el[1]
        try:
            new_el = next(iters[i])
            heappush(h, (new_el, i))
        except StopIteration:
            pass

        yield el[0]


'''
a = range(1, 100, 5)
b = range(0, 20, 2)
c = range(6, 16)

a = range(0, 20, 2)
b = range(0, 40, 4)
c = range(0, 10)

a = range(0, 20, 2)
b = range(0, 44, 4)
c = []

print(*a)
print(*b)
print(*c)

p = merge_sorter(a, b, c)

while True:
    try:
        print(next(p), end=' ')
    except Exception as e:
        break
'''
