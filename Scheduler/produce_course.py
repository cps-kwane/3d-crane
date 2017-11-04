#!/bin/env python
import random

N=50
barrier = 1
targets, obstacles = (20,'o'), (100,'x')

array = [['-' for i in range(N)] for j in range(N)]

for kind in (targets, obstacles):
	for i in range(kind[0]):
		x = random.randint(barrier+0,N-1-barrier)
		y = random.randint(barrier+0,N-1-barrier)
		while array[y][x] != '-':
			x = random.randint(barrier+0,N-1-barrier)
			y = random.randint(barrier+0,N-1-barrier)	
		array[y][x] = kind[1] 

f = open("course.txt","w")
for line in array: f.write("".join(line)+"\n")
f.close() 
	
		
