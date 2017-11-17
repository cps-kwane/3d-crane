#!/bin/env python
#Author: Philippos Papaphilipou
import sys
import copy
import math
sqrt2 = math.sqrt(2)
array = [list(line.strip()) for line in open("course.txt")]

N = len(array)

def distance(p1,p2):
	return math.sqrt((p1[0]-p2[0])**2+(p1[1]-p2[1])**2+0.0)
def count_obstacle_neighbours(p):
	count = 0
	for j in (-1,0,1):
			for i in (-1,0,1):
				if ((j,i) == (0,0)): continue
				y, x = p[0]+j,p[1]+i 
				if (N not in (y,x)) and (-1 not in (y,x)) and (array[p[0]+j][p[1]+i] == 'x'):
					count += 1
	return count
	
nodes_list = []
obsta_list = []
for j in range(N):
	for i in range(N):
		if array[j][i] == 'o':
			nodes_list.append((j,i)) 
		if array[j][i] == 'x':
			obsta_list.append((j,i)) 
ntargets = len(nodes_list)	


'''
# Recursive version - much slower
min_path = None
min_length = sys.maxint

def rec_shortest_hamiltonian_path(path,length):
	global min_length
	global min_path
	
	current = path[-1]
	
	if len(path)==ntargets+1:
		if length<min_length:
			min_length = length
			min_path = path
		return length
	
	for n in nodes_list:
		if n in path: continue
		
		rec_shortest_hamiltonian_path(list(path)+[n],length+distance(current,n))
		
rec_shortest_hamiltonian_path([(0,0)],0)

print min_path	
'''


# Traveling salesman - Dynamic programming version
import itertools

distances = [[distance (nodes_list[i],nodes_list[j]) for i in range(ntargets)] for j in range(ntargets)]

subset_costs = {}

for k in range(ntargets):
	subset_costs[tuple([k])]=(distance(nodes_list[k],(0,0)),k)
	
for subset_size in range(2, ntargets+1):
	for subset in itertools.combinations(range(ntargets), subset_size):
		min_dist = sys.maxint
		for m in subset:
			subset0 = list(subset)
			subset0.remove(m)
			subset0 = tuple(subset0)
			
			new_dist = subset_costs[subset0][0]+distances[subset_costs[subset0][1]][m]
			if new_dist<min_dist:
				subset_costs[subset]=(new_dist, m)
				min_dist = new_dist

print subset_costs[tuple(range(len(nodes_list)))]



# Trace solution
solution = []
current = tuple(range(len(nodes_list)))
while (len(current)!=0):
	solution.append(subset_costs[current][1])
	currentl=list(current)
	currentl.remove(subset_costs[current][1])
	current=tuple(currentl)
min_path =[(0,0)] + [nodes_list[n] for n in solution[::-1]]

	
quantized_path=[(0,0)]
combined=[(0,0)]


# This can be converted to recursive to be able to solve very complex mazes (AI) - now it may get for too many obstacles - BUG: works as gready
for n in range(len(min_path)-1):
	y,x = min_path[n]
	
	visited = [[False for i in range(N)] for j in range(N)]
	
	saw_obstacle = False
	buf = []
	last_angle = [0,0]
	while (y,x)!=min_path[n+1]:
		possible = []
		for j in (-1,0,1):
			for i in (-1,0,1):
				if (j,i) == (0,0) : continue 
				y0, x0 = y+j,x+i
				if (-1 in (y0,x0)) or (N in (y0,x0)): continue
				if array[y0][x0]!='x':	
					d = distance((y0,x0), min_path[n+1])						
					if d!=0:
						if 0 not in (j,i):
							d = distance((y+j/sqrt2,x+i/sqrt2), min_path[n+1])
						#d+= 0.5*count_obstacle_neighbours((y0,x0))
						if count_obstacle_neighbours((y0,x0))>1:
							continue							
					if not visited[y0][x0]: possible += [(d, y0, x0,j,i)]
				else:
					saw_obstacle = True			
		possible.sort()
		y,x = possible[0][1:3]
		angle = possible[0][3:5]
		#if last_angle!=angle:
		quantized_path+=[(y,x)]
		buf+=[(y,x)]
		visited[y][x]=True
	if saw_obstacle:
		combined+=buf
print quantized_path






# Plot a graph
import matplotlib.pyplot as plt
import numpy as np
		
plt.xlabel('x')
plt.ylabel('y')
plt.title('')#2d crane
plt.plot(np.array(min_path).T[0]+0.5, np.array(min_path).T[1]+0.5, 'g--' , label="best path when no x")

plt.plot(np.array(quantized_path).T[0]+0.5, np.array(quantized_path).T[1]+0.5, "y-", label="best path avoid obstacles")
plt.plot(np.array(nodes_list).T[0]+0.5, np.array(nodes_list).T[1]+0.5, "bo", mfc='none', label="targets")
plt.plot(np.array(obsta_list).T[0]+0.5, np.array(obsta_list).T[1]+0.5, "rx", label="obstacles")
plt.grid(True)

fig = plt.gcf();
ax = fig.add_subplot(1,1,1)   
major_ticks = np.arange(0, N+1, 10)                                              
minor_ticks = np.arange(0, N+1, 1)                                               
#ax.set_xticks(major_ticks)                                                       
ax.set_xticks(minor_ticks, minor=True)                                           
#ax.set_yticks(major_ticks)                                                       
ax.set_yticks(minor_ticks, minor=True)
ax.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=2, mode="expand", borderaxespad=0.)      

plt.grid(which='minor',color='#dddddd', linestyle=':', linewidth=1)

plt.ylim([0,N])
plt.xlim([0,N])

plt.savefig("picture.svg")
plt.show()

exit()




'''
next_positions = [[None for i in range(N)] for j in range(N)]

for j in range(N):
	for i in range(N):
		l = []
		
		for j0 in (-1,0,1):
			for i0 in (-1,0,1):
				if (j0,i0)==(0,0): continue
				y, x = j+j0, i+i0
				if (-1 in (y,x)) or (N in (y,x)) or (array[j][x]=='x'): continue
				last_point=(y,x)
				while array[y][x]=='-':
					y+=j0; x+= i0
					if (-1 in (y,x)) or (N in (y,x)):
						break
					if array[y][x] in ('o','-'):
						last_point=(y,x)
				l += [last_point]				
		next_positions[j][i] = l

min_length = sys.maxint
min_path = None



def rec(path, targets, length):	
	global min_length
	global min_path
	#print path
	coord = path[-1]
	current = array[coord[0]][coord[1]]
	if current == 'x' or length>min_length:
		return

	if current == 'o':
		targets += 1
		if targets == ntargets:
			min_length = length
			min_path = list(path)
			#print "======================================="
			return
	
	for j in (-1,0,1):
		for i in (-1,0,1):
			if ((j,i) == (0,0)): continue
			
			y, x = coord[0]+j, coord[1]+i
			if (-1 in (y,x)) or (N in (y,x)) or ((y,x) in path): continue
			
			rec(list(path)+[(y,x)], targets, length+distance(coord,(y,x)))

rec([(0,0)], 0, 0)
print min_path
'''
