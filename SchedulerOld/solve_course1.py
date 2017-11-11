#!/bin/env python
#Author: Philippos Papaphilipou
import sys
import copy
import math
sqrt2 = math.sqrt(2)
array = [list(line.strip()) for line in open("course.txt")]

N = len(array)



nodes_list = []
obsta_list = []
for j in range(N):
	for i in range(N):
		if array[j][i] == 'o':
			nodes_list.append((j,i)) 
		if array[j][i] == 'x':
			obsta_list.append((j,i)) 
ntargets = len(nodes_list)


def distance(p1,p2):
	return math.sqrt((p1[0]-p2[0])**2+(p1[1]-p2[1])**2+0.0)

def in_obstacle_border(y,x):
	for n in obsta_list:
		if (abs(n[0]-y)<=1) and (abs(n[1]-x)<=1):
			return True
	return False 
	
def count_obstacle_neighbours(p):
	count = 0
	for j in (-1,0,1):
			for i in (-1,0,1):
				if ((j,i) == (0,0)): continue
				y, x = p[0]+j,p[1]+i 
								
				if (y>N) or (y<0) or (x>N) or (x<0) or  in_obstacle_border(p[0],p[1]):
					count += 1
	return count


	

	


	
	
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




min_path_ = None
min_length_ = sys.maxint
terminated = False
goal = None

#queue = []

#while (len(queue)!=0):

def rec_a_star(path,length):
	global min_length_
	global min_path_
	global terminated
	global goal
	
	if terminated: return
	
	current = path[-1]
	y,x = current[0],current[1]
	print current
	if current == goal:
		if length<min_length_:			
			min_length_ = length
			min_path_ = path
			terminated = True
		return length
	
	possible = []
	for j in (-1,0,1):
		for i in (-1,0,1):
			if (j,i) == (0,0) : continue 
			y0, x0 = y+j,x+i
			if (-1 in (y0,x0)) or (N in (y0,x0)) or ((y0,x0) in path): continue
			if not in_obstacle_border(y0,x0):	
				d = distance((y0,x0), goal)						
				#if d!=0:
					#if 0 not in (j,i):
					#	d = distance((y+j/sqrt2,x+i/sqrt2), goal)
				d *= 0.5+count_obstacle_neighbours((y0,x0))
					#if count_obstacle_neighbours((y0,x0))>1:#fix
					#	continue							
				possible += [(d, y0, x0)]
			#else:
			#	saw_obstacle = True			
	possible.sort()
	#print possible
	for n in possible:
		n = n[1:3]
		rec_a_star(list(path)+[n],length+distance(current,n))
		if terminated: return


quantized_path=[(0,0)]

for n in range(len(min_path)-1):
	start, goal = min_path[n], min_path[n+1]
	min_path_ = None
	min_length_ = sys.maxint
	
	terminated = False
	rec_a_star([start],0)
	
	quantized_path+=min_path_


# Plot a graph
import matplotlib.pyplot as plt
import numpy as np
		
plt.xlabel('x')
plt.ylabel('y')
plt.title('')#2d crane
plt.plot(np.array(min_path).T[0], np.array(min_path).T[1], 'g--' , label="best path when no x")

plt.plot(np.array(quantized_path).T[0], np.array(quantized_path).T[1], "y-", label="best path avoid obstacles")
plt.plot(np.array(nodes_list).T[0], np.array(nodes_list).T[1], "bo", mfc='none', label="targets")
plt.plot(np.array(obsta_list).T[0], np.array(obsta_list).T[1], "rx", label="obstacles")
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

ax = fig.add_subplot(1,1,1) 
import matplotlib.patches as patches
for n in nodes_list+obsta_list:
	ax.add_patch( patches.Rectangle( (n[0]-1,n[1]-1), 2, 2, fill=False ))#, alpha=0.6






plt.savefig("picture.svg")
plt.show()

exit()


