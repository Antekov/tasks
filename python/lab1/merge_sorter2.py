from heapq import heappush, heappop


def merge_sorter(*iterables):
    h = []

    iters = []

    # ids = list(range(len(iterables)))

    for i, it in enumerate(iterables):
        iters.append(iter(it))
        el = next(iters[-1])
        heappush(h, (el, i))

    # print('Init:', h)

    while True:
        # print(h)
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
            # print('Empty iterator #', i)
            # ids.remove(i)
            # if len(ids) == 0:
            #     break

        yield el[0]


a = range(1, 100, 5)
b = range(0, 20, 2)
c = range(6, 16)

a = range(0, 20, 2)
b = range(0, 40, 4)
c = range(0, 10)

a = range(0, 20, 2)
b = range(0, 40, 4)
c = range(0, 20)

print(*a)
print(*b)
print(*c)

p = merge_sorter(a, b, c)

while True:
    try:
        print(next(p), end=' ')
    except Exception as e:
        break
