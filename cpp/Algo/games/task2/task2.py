# https://www.e-olymp.com/ru/submissions/8012686
import sys
sys.setrecursionlimit(10000)
n = 8

usedPositions = set()
winPositions = set()
losePositions = set()

walls = set()

g = dict()

def isRunnerStep(pos) -> bool:
    return pos[2]

def isTermyWin(pos, walls) -> bool:
    x1 = pos[0] % n
    y1 = pos[0] // n

    x2 = pos[1] % n
    y2 = pos[1] // n

    if x1 == x2 and y1 == y2:
        return True

    if (x1 - x2 == 0 or y1 - y2 == 0 or abs(x1 - x2) == abs(y1 - y2)):
        # check walls
        if x1 == x2:
            for y in range(min(y1, y2) + 1, max(y1, y2)):
                if (y, x1) in walls:
                    return False
        elif y1 == y2:
            for x in range(min(x1, x2) + 1, max(x1, x2)):
                if (y1, x) in walls:
                    return False
        else:
            stepx = 1 if x2 > x1 else -1
            stepy = 1 if y2 > y1 else -1
            for x, y in zip(range(x1 + stepx, x2, stepx), range(y1 + stepy, y2, stepy)):
                if (y, x) in walls:
                    return False
               
        return True
    
    return False

def isRunnerWin(pos, walls) -> bool:
    if isTermyWin(pos, walls): 
        return False

    if isRunnerStep(pos):
        y1 = pos[0] // n

        if y1 == n-1:
            return True
        
    return False


def isTerminal(pos, walls) -> bool:
    if isRunnerWin(pos, walls):
        return True
            
    if isTermyWin(pos, walls):
        return True
    
    return False


def makeStep(pos, walls): 
    dx = [-1, -1, -1,  0, 0,  1, 1, 1]
    dy = [-1,  0,  1, -1, 1, -1, 0, 1]

    nextPositions = []

    if isRunnerStep(pos):
        x = pos[0] % n
        y = pos[0] // n
    else:
        x = pos[1] % n
        y = pos[1] // n
    
    for i in range(8):
        px = x + dx[i]
        py = y + dy[i]

        if px < 0 or px >= n or py < 0 or py >= n:
            continue

        if (py, px) in walls:
            continue
        
        if isRunnerStep(pos):
            runner = py * n + px
            termy = pos[1]
        else:
            runner = pos[0]
            termy = py * n + px

        step = not pos[2]

        nextPositions.append((runner, termy, step))
    
    usedPositions.add(pos)
    
    return nextPositions
'''
used = set()
def dfs(u, N, P):
    used.add(u)
    print(f'{u} - Used: {len(used)} | N: {len(N)} | P: {len(P)}')
    if u in N or u in P:
        return
    for v in g[u]:
        if v not in used:
            dfs(v, N, P)
    c = 0
    for v in g[u]:
        if v in P:
            N.add(u)
            break
        if v in N:
            c += 1
    else:
        if (c == len(g[u])):
            P.add(u)
        else:
            pass
            # raise ValueError
'''

def solve(runner, termy, walls):
    startPosition = (runner, termy, True)

    q = []

    q.append(startPosition)

    while len(q) > 0:
        position = q[0]
        # print("Get from queue:", position)
        del q[0]

        if isTerminal(position, walls):
            if isRunnerStep(position):
                if isRunnerWin(position, walls):
                    # print(f'Runner Win - add {position} to N')
                    winPositions.add(position)
                else:
                    # print(f'Runner Lose - add {position} to P')
                    losePositions.add(position)
            else:
                if isTermyWin(position, walls):
                    # print(f'Termy Win - add {position} to N')
                    winPositions.add(position)
                else:
                    # print(f'Termy Lose - add {position} to P')
                    losePositions.add(position)

            usedPositions.add(position)
        else:
            nextPositions = makeStep(position, walls)
            g[position] = nextPositions
            for nextPosition in nextPositions:
                if nextPosition not in usedPositions and \
                    nextPosition not in q:
                    # print(nextPosition, '- Add to queue')
                    q.append(nextPosition)

        # print(f'Pos count: {len(usedPositions)} | Q count: {len(q)}')

    # print(len(winPositions))
    # print(len(losePositions))
    # print(len(usedPositions))

    N = winPositions
    P = losePositions

    

    U = usedPositions
    U = (U - P) - N

    '''
    for position in P | N:
        if position not in used:
            dfs(position, N, P)
            print(f'U: {len(U)} | N: {len(N)} | P: {len(P)}')
    '''
    # print('Start position:', startPosition)
    print(f'Start: U: {len(U)} | N: {len(N)} | P: {len(P)}')
    
    while len(U) > 0 and startPosition not in N and startPosition not in P:
        R = set()
        for u in U:
            c = 0
            for v in g[u]:
                if v in P:
                    # print(u, '- Add to N')
                    N.add(u) 
                    R.add(u)
                    break
                if v in N:
                    c += 1
            else:
                if c == len(g[u]):
                    # print(u, '- Add to P')
                    P.add(u)
                    R.add(u)
        if len(R) > 0:
            U -= R
        else:
            # print(f'Break U: {len(U)} | N: {len(N)} | P: {len(P)}') 
            break

        # print(f'U: {len(U)} | N: {len(N)} | P: {len(P)}')          


    if startPosition in winPositions:
        print(1)
    elif startPosition in losePositions:
        print(-1)
    else:
        print(-2)


f = open('input.txt', 'r')

for i in range(n):
    s = f.readline().strip()
    for j in range(n):
        if s[j] == '1':
            walls.add((i, j))
        elif s[j] == '2':
            runner = i*n + j
        elif s[j] == '3':
            termy = i*n + j

f.close()

solve(runner, termy, walls)