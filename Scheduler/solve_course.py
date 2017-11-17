#!/bin/env python
#Author: Philippos Papaphilippou
import sys
import copy
import math
sqrt2 = math.sqrt(2)

array = [list(line.strip()) for line in open("course.txt")]
N = len(array)
draw_results = True # If False, no matplotlib or a computer moniter are needed
debug = False 

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

	
# Recursive version - good for upto 10 points (dynamic programming coming soon)
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

# Build heatmap for heuristics
obstacle_heatmap = [[0 for i in range(N)] for j in range(N)]
min_ = sys.maxint
max_ = -sys.maxint
for y in range(N):
	for x in range(N):
		for n in obsta_list:
			if n!=(y,x):
				obstacle_heatmap[y][x]+=1.0/(distance(n,(y,x))**1.7)
		if (y,x) not in obsta_list:
			if obstacle_heatmap[y][x]>max_:max_=obstacle_heatmap[y][x]
			if obstacle_heatmap[y][x]<min_:min_=obstacle_heatmap[y][x]

# Normalize heatmap		
for y in range(N):
	for x in range(N):		
		if (y,x) in obsta_list:
			obstacle_heatmap[y][x]=1
		else:
			obstacle_heatmap[y][x]=(obstacle_heatmap[y][x]-min_)/(max_-min_)

if debug: print min_path

# AI algorithm to avoid obstacles
if debug: print "starting A*"
def a_star(start, goal):
	queue = [(0,[start],0,0)]
	#visited = [[False for i in range(N)] for j in range(N)]
	
	min_cost=dict()
	
	while (len(queue)!=0):		
		candidate = queue[0]
		queue=queue[1:]

		path = candidate[1]
		current = path[-1]
		length = candidate[2]
		hops = candidate[3]
		y,x = current[0],current[1]

		if current == goal:
			return path
		count=0
		for j in (-1,0,1):
			for i in (-1,0,1):
				if (j,i) == (0,0): continue 
				y0, x0 = y+j,x+i
				n=(y0,x0)
				if (-1 in n) or (N in n) or (n in path): continue
				if not in_obstacle_border(y0,x0):	
					d = distance((y0,x0), goal)						
					
					if n in min_cost:
						if min_cost[n]<d+length:
							continue
					min_cost[n]=d+length
					
					# (better but more manoeuvres for crane)
					#if 0 not in (j,i):
					#	d = distance((y+j/sqrt2,x+i/sqrt2), goal)
					
					# HEURISTICS (subject to fine-tune)	
					#score = d + 0.1*length + 0.1*count_obstacle_neighbours((y0,x0)) 
					#score = d + 4 * obstacle_heatmap[y][x] + 0.1* length	
					#score = d**2 #+ obstacle_heatmap[y][x] * length		
					score = d*(0.1+obstacle_heatmap[y][x]) + 0.1*length 	
					
					#print score
					#print queue[0:5]
					# Insertion sort
					for k in range(len(queue)+1):
						if (k == len(queue)) or (queue[k][0]>=score):
							queue.insert(k, (score,list(path)+[n],length+distance(current,n),hops+1))
							count +=1
							break

quantized_path=[(0,0)]

# Run A* for every 2 consecutive targets in the shortest path list
for n in range(len(min_path)-1):
	if debug: print "%d/%d"%(n, len(min_path)-1)
	start, goal = min_path[n], min_path[n+1]
	
	min_path_=a_star(start,goal)
	
	quantized_path+=min_path_
	
if debug: print "%d/%d"%(len(min_path)-1, len(min_path)-1)

# Remove unnecessary points 	
comp_path = [(0,0)]
for n in range(1,len(quantized_path)-1):
	prev, cur, next = quantized_path[n-1], quantized_path[n], quantized_path[n+1]
	if ((prev[0]-cur[0]!=cur[0]-next[0]) or (prev[1]-cur[1]!=cur[1]-next[1])) and (prev!=cur):
		comp_path.append(cur)
comp_path.append(quantized_path[-1])

for n in comp_path:
	print "%d\t%d"%n

# Plot a graph
if draw_results:
	import matplotlib.pyplot as plt
	import numpy as np
		
	plt.xlabel('x')
	plt.ylabel('y')
	plt.title('')
	plt.plot(np.array(min_path).T[0], np.array(min_path).T[1], 'r--' , label="best path (TSP)")
	plt.plot(np.array(comp_path).T[0], np.array(comp_path).T[1], "b-", label="A* avoid obstacles")
	plt.plot(np.array(nodes_list).T[0], np.array(nodes_list).T[1], "bo", mfc='none', label="targets")
	plt.plot(np.array(obsta_list).T[0], np.array(obsta_list).T[1], "rx", label="obstacles")
	plt.grid(True)

	fig = plt.gcf();
	ax = fig.add_subplot(1,1,1)   
	major_ticks = np.arange(0, N+1, 10)                                              
	minor_ticks = np.arange(0, N+1, 1)                                               
	ax.set_xticks(minor_ticks, minor=True)                                           
	ax.set_yticks(minor_ticks, minor=True)
	ax.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=2, mode="expand", borderaxespad=0.)      

	plt.grid(which='minor',color='#dddddd', linestyle=':', linewidth=1)

	plt.ylim([0,N])
	plt.xlim([0,N])

	ax = fig.add_subplot(1,1,1) 
	import matplotlib.patches as patches

	# Paint Heatmap
	for y in range(N):
		for x in range(N):
			ax.add_patch( patches.Rectangle( (y-0.5,x-0.5), 1, 1, fill=True, linewidth=0,facecolor="#106d00", alpha=obstacle_heatmap[y][x]))

	# White boxes for targets and obstacles			
	for n in nodes_list+obsta_list:
		ax.add_patch( patches.Rectangle( (n[0]-1,n[1]-1), 2, 2, fill=True,facecolor="#ffffff",edgecolor="#000000"))


	plt.savefig("picture.svg")
	plt.show()

exit()

