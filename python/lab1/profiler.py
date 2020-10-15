import sys
import functools
import time


def profiler(func):
    calls = 0
    func.calls = 0
    func.last_time_taken = 0

    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        nonlocal calls
        # print('wrapper.calls =', wrapper.calls,
        # '| wrapper.last_time_taken = ', wrapper.last_time_taken)
        if calls == 0:
            wrapper.calls = 0
            wrapper.start_time = time.time()

        calls += 1
        value = func(*args, **kwargs)
        calls -= 1
        wrapper.calls += 1
        wrapper.last_time_taken = time.time() - wrapper.start_time

        return value

    return wrapper


'''
def wrapper(*args, **kwargs):
        nonlocal calls
        if not calls:
            wrapper.calls = 0

        calls += 1
        result = func(*args, **kwargs)
        calls -= 1
        wrapper.calls += 1

        return result
'''

'''
@profiler
def akkerman(m, n):
    "Akkerman function"
    # print('akkerman(', m, n, ')')
    if m == 0:
        return (n+1)
    if m > 0 and n == 0:
        return akkerman(m-1, 1)
    if m > 0 and n > 0:
        return akkerman(m-1, akkerman(m, n-1))


@profiler
def sleepy_recursion(n):
    "I am sleepy"
    time.sleep(1)
    print('Call', n)
    if n > 1:
        sleepy_recursion(n-1)


# sleepy_recursion(3)

print(sleepy_recursion.__doc__)
print(sleepy_recursion.calls)
print(sleepy_recursion.last_time_taken)


akkerman(2, 5)

print(akkerman.__doc__)
print(akkerman.calls)
print(akkerman.last_time_taken)
'''
