#!/bin/env python
# Author: Philippos Papaphilippou
import random

N = 50
barrier = 3
targets, obstacles = (3, '1'), (3, '-1')


# This function avoids overlapping boundaries
def neighbour_in_bound(x, y, array):
    for j in (-1, 0, 1):
        for i in (-1, 0, 1):
            if (j, i) == (0, 0):
                continue
            y0, x0 = y + j, x + i
            if (-1 in (y0, x0)) or (N in (y0, x0)):
                continue
            if array[y0][x0] != '-':
                return True
    return False


def produce_fn():
    array = [['-' for i in range(N)] for j in range(N)]
    for kind in (targets, obstacles):
        for i in range(kind[0]):
            x = random.randint(barrier + 0, N - 1 - barrier)
            y = random.randint(barrier + 0, N - 1 - barrier)
            while (array[y][x] != '-') or (neighbour_in_bound(x, y, array)):
                x = random.randint(barrier + 0, N - 1 - barrier)
                y = random.randint(barrier + 0, N - 1 - barrier)
            array[y][x] = kind[1]

    f = open("course_random.csv", "w")
    for j in range(N):
        for i in range(N):
            if array[j][i] != '-':
                f.write("%d,%d,%s\n" % (j, i, array[j][i]))
    f.close()
    complete = float(2)
    return complete
