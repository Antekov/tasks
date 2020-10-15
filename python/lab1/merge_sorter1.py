from heapq import heappush, heappop


def merge_sorter(*iterables):
    h = []
    for it in iterables:
        for el in it:
            heappush(h, el)

    while True:
        try:
            el = heappop(h)
        except Exception:
            raise StopIteration

        yield el


a = range(1, 100, 5)
b = range(0, 20, 2)
c = range(6, 16)

p = merge_sorter(a, b, c)

while True:
    try:
        print(next(p), end=' ')
    except Exception:
        break
