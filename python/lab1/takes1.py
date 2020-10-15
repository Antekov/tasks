def takes(*types, **kwtypes):
    def takes_decorator(func):
        def wrapper(*args, **kwargs):
            print(*types)
            print(*args)
            func(*args, **kwargs)
        return wrapper
    return takes_decorator




def add_line(line):
    def qwerty1(f):
        def qwerty(*args, **kwargs):
            print(line)
            f(*args, **kwargs)
        return qwerty
    return qwerty1


@add_line('-----------')
def myfunc(a, b, c):
    print('a b c:', a, b, c)


@add_line('============')
def myfunc2(a, b, c, d=100):
    print('a b c d:', a, b, c, d)


myfunc(1, 2, c=3)
myfunc2(5, 6, 7, 8)
