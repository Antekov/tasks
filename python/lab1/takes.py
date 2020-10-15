import sys
import functools


def takes(*types, **kwtypes):
    def takes_decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            for i, t in enumerate(types):
                # print('Arg {} must have type {}'.format(i, t))
                # print('Arg {} has type {}'.format(i, type(args[i])))
                if i < len(args):
                    if not isinstance(args[i], t):
                        raise TypeError
                else:
                    break
            func(*args, **kwargs)
        # wrapper.__name__ = func.__name__
        # wrapper.__doc__ = func.__doc__
        # wrapper.__module__ = func.__module__
        return wrapper

    return takes_decorator


exec(sys.stdin.read())
