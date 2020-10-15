@takes(int, str)
def f(a, b):
    print(a, b)


try:
    f(1, 2)
except Exception as e:
    print(type(e).__name__)
