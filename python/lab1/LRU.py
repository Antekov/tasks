def cache(n):
    def cache_decorator(func):
        d = dict()
        indexes = []

        def wrapper(*args, **kwargs):
            # print(len(args) > 0, len(kwargs) > 0)

            if len(args) == 0:
                key = [k for k in kwargs.keys()]
                key += [v for v in kwargs.values()]
                key = tuple(key)
            else:
                key = [v for v in args]
                key += [k for k in kwargs.keys()]
                key += [v for v in kwargs.values()]
                key = tuple(key)
            if key in d:
                return d[key]
            d[key] = func(*args, **kwargs)
            indexes.append(key)
            if len(indexes) > n:
                del[d[indexes[0]]]
                del[indexes[0]]

            # print(indexes)
            # print(d)
            return d[key]
        wrapper.__name__ = func.__name__
        wrapper.__doc__ = func.__doc__
        wrapper.__module__ = func.__module__
        return wrapper
    return cache_decorator


'''
@cache(2)
def akkerman(m, n):
    "Akkerman function"
    # print('akkerman(', m, n, ')')
    if m == 0:
        return (n+1)
    if m > 0 and n == 0:
        return akkerman(m-1, 1)
    if m > 0 and n > 0:
        return akkerman(m-1, akkerman(m, n-1))


def akkerman2(m, n):
    "Akkerman2 function"
    # print('akkerman(', m, n, ')')
    if m == 0:
        return (n+1)
    if m > 0 and n == 0:
        return akkerman2(m-1, 1)
    if m > 0 and n > 0:
        return akkerman2(m-1, akkerman2(m, n-1))


for n in range(1, 4):
    for m in range(1, 7):
        print(n, m, akkerman2(n, m), ' = ', akkerman2(n, m))


@cache(2)
def foo(*args, **kwargs):
    "Foo qtwrt"
    print('calculate foo for {}'.format((*args, kwargs)))
    res = args[0] if len(args) > 0 else None
    return res


foo(1)
foo(2)
foo(1)
foo(2)
foo(1)
foo(3)
foo(1)

foo(1, 2, 3)
foo(a=1, b=2, c=3)
foo(1, 2, 3, a=1, b=2, c=3)

print(foo.__doc__)
'''
