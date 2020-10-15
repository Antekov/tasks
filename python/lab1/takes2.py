import sys
import functools


def takes(*types, **kwtypes):
    def takes_decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            for i, t in enumerate(types):
                # print('Arg {} must have type {}'.format(i, t))
                # print('Arg {} has type {}'.format(i, type(args[i])))
                if not isinstance(args[i], t):
                    raise TypeError
            func(*args, **kwargs)
        # wrapper.__name__ = func.__name__
        # wrapper.__doc__ = func.__doc__
        # wrapper.__module__ = func.__module__
        return wrapper

    return takes_decorator


@takes(int, int, str)
def myfunc(a, b, c):
    '''Function prints three arguments'''
    print('a b c:', a, b, c)


print(myfunc.__name__)
print(myfunc.__doc__)
print(myfunc.__module__)

try:
    myfunc(1, 2, 'asdf')
except:
    pass
