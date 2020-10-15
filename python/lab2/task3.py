import sys


for line in sys.stdin:
    parts = line.rstrip().split('\t')

    print('{0}{1:.>73}'.format(parts[0][:7], parts[4]))
