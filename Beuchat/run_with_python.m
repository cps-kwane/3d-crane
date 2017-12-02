%%% Given Setup Script
clear variables
close all
clear all
clc
%% SimscapeCrane_MPC_start;
load('Params_Simscape.mat');
load('SSmodelParams.mat');
%% Load the dynamics matrices using a solution from last assignment
Ts=1/20;
T=10;
x0=[0 0 0 0 0 0 0 0]'; % starting offset

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

%% Obtain waypoints through python script

%Enable Running python Script From Matlab
% if count(py.sys.path,'') == 0
%     insert(py.sys.path,int32(0),'');
% end
%Run Full Script Once to Ensure No errors
% if(system('python -B solve_course_csv.py')==0)  %DON'T CACHE -B
%     display('no errors')
% end

%% Generate Random Course
%flag=0;
%flag=py.create_csv_course.produce_fn()

%while(flag~=2)
%	flag=flag
%end
% Store points to compute score later
[obstacles,targets]=getCourseFromCSV('course_.csv');

%% Initialize PID Parameters

Ki=0.2;
Kia=-0.3;
Kp=6;
Kpa=4;

Kix=0.2;
kiax=20;
Kpx=11.9;
Kpax=4;


%% Timing Starts Now

%% Obtain List of Points
tic;
waypoints_list= py.solve_course_csv.find_result('course_.csv');
%Convert python list to matlab datastruct
total_waypoints=length(waypoints_list);
waypoints_cell=cell(waypoints_list);
xwaypoints_cell=cell(total_waypoints,1);
ywaypoints_cell=cell(total_waypoints,1);
disp(waypoints_cell);

for i=1:total_waypoints
	  xwaypoints_cell{i}=waypoints_cell{i}{1};
    ywaypoints_cell{i}=waypoints_cell{i}{2};
	  xwaypoints(i)=double(xwaypoints_cell{i})/100;
	  ywaypoints(i)=double(ywaypoints_cell{i})/100;
end



%% Run Simulation
START_COURSE=1;
modelName='high_level';
simout= sim(modelName,'FixedStep',num2str(Ts),'ReturnWorkspaceOutputs','on');
fprintf('time taken = %f',toc)
mscore = simple_getScore(simout, obstacles, targets,1)

%delete('course_.csv');

