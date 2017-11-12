%%% Given Setup Script
clear variables
close all
clc
%% SimscapeCrane_MPC_start;
load('Params_Simscape.mat');
load('SSmodelParams.mat');
%% Load the dynamics matrices using a solution from last assignment
Ts=1/20;
T=10;
x0=[xRange(2)/2 0 yRange(2)/2 0 0 0 0 0]'; % starting offset

%% Refine friction model
TxVisc = 49.1750;
TxCoulomb = 2.5;
TxBreak = 0;
xZero = 0;

yZero = 0;
TyBreak = 0;
TyVisc = 47.5650;
TyCoulomb = 1.8;

% TzVisc = 92.5; % considering the mass added
TzVisc = 342; %Z friciton without contant frictional force added by the 
%mass


%% Run Python Script to get points

%Enable Running python Script From Matlab
if count(py.sys.path,'') == 0
    insert(py.sys.path,int32(0),'');
end
%Run Full Script Once to Ensure No errors
if(system('python -B points_scheduler.py')==0)  %DON'T CACHE -B
    display('no errors')
end

%Obtain List of Points
waypoints_list= py.points_scheduler.find_result('course.txt');
%Convert python list to matlab datastruct
num_waypoints=length(waypoints_list);
waypoints_cell=cell(waypoints_list);
xwaypoints_cell=cell(15,1);
ywaypoints_cell=cell(15,1);
disp(waypoints_cell)
for i=1:num_waypoints
	xwaypoints_cell{i}=waypoints_cell{i}{1}
	ywaypoints_cell{i}=waypoints_cell{i}{2}
	xwaypoints(i)=double(xwaypoints_cell{i})
	ywaypoints(i)=double(ywaypoints_cell{i})
end
%Path has been obtained

%%Start Simulink Model


	




%%





