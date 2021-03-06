#!/bin/env python
#Author: Philippos Papaphilippou
import random

N=50
barrier = 3
targets, obstacles = (10,'o'), (100,'x')

array = [['-' for i in range(N)] for j in range(N)]

# This function avoids overlapping boundaries
def neighbour_in_bound(x,y):
	for j in (-1,0,1):
		for i in (-1,0,1):
			if (j,i) == (0,0): continue 
			y0, x0 = y+j,x+i
			if (-1 in (y0,x0)) or (N in (y0,x0)): continue
			if array[y0][x0]!='-':
				return True
	return False

for kind in (targets, obstacles):
	for i in range(kind[0]):
		x = random.randint(barrier+0,N-1-barrier)
		y = random.randint(barrier+0,N-1-barrier)
		while (array[y][x] != '-') or (neighbour_in_bound(x,y)):
			x = random.randint(barrier+0,N-1-barrier)
			y = random.randint(barrier+0,N-1-barrier)	
		array[y][x] = kind[1] 

f = open("course.txt","w")
for line in array: f.write("".join(line)+"\n")
f.close() 
	
		
