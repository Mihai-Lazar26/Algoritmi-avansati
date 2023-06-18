
INF = 1000000001
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

def findPointPoz(vec, pt):
    for i in range(len(vec)):
        if vec[i].x == pt.x and vec[i].y == pt.y:
            return i
    return -1

def nextPoz(val, n, pas):
    a = (val + pas) % n
    if(a < 0):
        return n + a
    return a
def problema2():
    n = int(input())
    poligon = []
    minX = Point(INF, 0)
    maxX = Point(-INF, 0)
    minY = Point(0, INF)
    maxY = Point(0, -INF)
    for i in range(n):
        linie = input().strip().split()
        x = int(linie[0])
        y = int(linie[1])
        pt = Point(x, y)
        poligon.append(pt)
        if minX.x > pt.x:
            minX.x = pt.x
            minX.y = pt.y

        if maxX.x < pt.x:
            maxX.x = pt.x
            maxX.y = pt.y


        if minY.y > pt.y:
            minY.x = pt.x
            minY.y = pt.y


        if maxY.y < pt.y:
            maxY.x = pt.x
            maxY.y = pt.y

    primul = findPointPoz(poligon, minX)
    ultimul = findPointPoz(poligon, maxX)

    a = primul
    b = ultimul
    okX = True
    while a != b and okX:
        curent = poligon[a].x
        urmatorul = poligon[nextPoz(a, len(poligon), 1)].x

        if urmatorul < curent:
            okX = False

        a = nextPoz(a, len(poligon), 1)

    a = primul
    b = ultimul
    while a != b and okX:
        curent = poligon[a].x
        urmatorul = poligon[nextPoz(a, len(poligon), -1)].x

        if urmatorul < curent:
            okX = False

        a = nextPoz(a, len(poligon), -1)

    primul = findPointPoz(poligon, minY)
    ultimul = findPointPoz(poligon, maxY)

    a = primul
    b = ultimul
    okY = True
    while a != b and okY:
        curent = poligon[a].y
        urmatorul = poligon[nextPoz(a, len(poligon), 1)].y

        if urmatorul < curent:
            okY = False

        a = nextPoz(a, len(poligon), 1)

    a = primul
    b = ultimul
    while a != b and okY:
        curent = poligon[a].y
        urmatorul = poligon[nextPoz(a, len(poligon), -1)].y

        if urmatorul < curent:
            okY = False

        a = nextPoz(a, len(poligon), -1)

    if okX:
        print('YES')
    else:
        print('NO')

    if okY:
        print('YES')
    else:
        print('NO')

def detAux3(A, B, C):
    val1 = A.x * B.y * (C.x ** 2 + C.y ** 2) + B.x * C.y * (A.x ** 2 + A.y ** 2) + C.x * A.y * (B.x ** 2 + B.y ** 2)
    val2 = - (A.x ** 2 + A.y ** 2) * B.y * C.x - (B.x ** 2 + B.y ** 2) * C.y * A.x - (C.x ** 2 + C.y ** 2) * A.y * B.x

    return val1 + val2

def detProblema3(A, B, C, P):
    # i p i p
    val = - detAux3(B, C, P) + detAux3(A, C, P) - detAux3(A, B, P) + detAux3(A, B, C)
    return val

def undeInCerc(A, B, C, P):
    val = detProblema3(A, B, C, P)
    if val == 0:
        return 'BOUNDARY'
    if val < 0:
        return 'OUTSIDE'

    return 'INSIDE'

def problema3():
    linie = input().strip().split()
    A = Point(int(linie[0]), int(linie[1]))

    linie = input().strip().split()
    B = Point(int(linie[0]), int(linie[1]))

    linie = input().strip().split()
    C = Point(int(linie[0]), int(linie[1]))

    m = int(input())
    raspunsuri = []
    for i in range(m):
        linie = input().strip().split()
        punct = Point(int(linie[0]), int(linie[1]))
        raspunsuri.append(undeInCerc(A, B, C, punct))

    for val in raspunsuri:
        print(val)

def problema4():
    linie = input().strip().split()
    A = Point(int(linie[0]), int(linie[1]))

    linie = input().strip().split()
    B = Point(int(linie[0]), int(linie[1]))

    linie = input().strip().split()
    C = Point(int(linie[0]), int(linie[1]))

    linie = input().strip().split()
    D = Point(int(linie[0]), int(linie[1]))

    AC = detProblema3(A, B, C, D)
    BD = detProblema3(B, C, D, A)

    if AC > 0:
        print('AC: ILLEGAL')
    else:
        print('AC: LEGAL')

    if BD > 0:
        print('BD: ILLEGAL')
    else:
        print('BD: LEGAL')







if __name__ == '__main__':
    problema4()
