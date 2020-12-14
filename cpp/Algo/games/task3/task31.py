n = int(input())
# https://www.e-olymp.com/ru/submissions/8012686

usedPositions = set()
winPositions = set()
losePositions = set()

walls = set()

g = dict()

def isRunnerStep(pos) -> bool:
    return pos[0]

def isTermyWin(pos) -> bool:
    if not isRunnerStep(pos) and len(pos[1]) == 0:
        return False
    return True

def isRunnerWin(pos) -> bool:
    if isRunnerStep(pos) and len(pos[1]) == 0:
        return False
        
    return True


def isTerminal(pos) -> bool:
    return len(pos[1]) == 0

def makeStep(pos): 
    nextPositions = []

    for i in range(len(pos[1])):
        groups = pos[1]
        nextGroups = list(groups[:i]) + list(groups[i+1:])
        if groups[i] == 2:
            nextPositions.append((not pos[0], tuple(sorted(nextGroups))))
        elif groups[i] == 3:
            nextPositions.append((not pos[0], tuple(sorted(nextGroups))))
            nextPositions.append((not pos[0], tuple(sorted(nextGroups + [2]))))
        elif groups[i] == 4:
            nextPositions.append((not pos[0], tuple(sorted(nextGroups + [3]))))
            nextPositions.append((not pos[0], tuple(sorted(nextGroups + [2]))))
        else:
            nextPositions.append((not pos[0], tuple(sorted(nextGroups + [groups[i]-1]))))
            nextPositions.append((not pos[0], tuple(sorted(nextGroups + [groups[i]-2]))))
            for j in range(3, (groups[i] + groups[i] % 2) // 2 + 1):
                nextPositions.append((not pos[0], tuple(sorted(nextGroups + [j-1, groups[i] - j]))))
    
    usedPositions.add(pos)
    
    return nextPositions

def solve(n):
    startPosition = (True, (n,))

    q = []

    q.append(startPosition)

    while len(q) > 0:
        position = q[0]
        # print("Get from queue:", position)
        del q[0]
        
        if isTerminal(position):
            if isRunnerStep(position):
                if isRunnerWin(position):
                    # print(f'Runner Win - add {position} to N')
                    winPositions.add(position)
                else:
                    # print(f'Runner Lose - add {position} to P')
                    losePositions.add(position)
            else:
                if isTermyWin(position):
                    # print(f'Termy Win - add {position} to N')
                    winPositions.add(position)
                else:
                    # print(f'Termy Lose - add {position} to P')
                    losePositions.add(position)

            usedPositions.add(position)
        else:
            nextPositions = makeStep(position)
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

    #print('Start position:', startPosition)
    #print(f'Start: U: {len(U)} | N: {len(N)} | P: {len(P)}')
    
    while len(U) > 0:
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

    #print(losePositions)

    if startPosition in winPositions:
        print('Schtirlitz')
        w = []
        if (n == 2):
            w += [1, 2]
        elif n == 3:
            w += [2]
        else:
            if (False, (n - 1,)) in losePositions:
                w += [1, n]

            if (False, (n - 2,)) in losePositions:
                w += [2, n - 1]

            for i in range(3, n - 1):
                if (False, (i-1, n-i)) in losePositions:
                    w += [i]

        print(*sorted(w), sep='\n')

    else:
        print('Mueller')

solve(n)
