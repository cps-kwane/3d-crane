%{
This script takes in a .csv input file and uses it to generate the waypoints to be visited
as well as the obstacles and targets arrays to be used for score calculation.
%}

%% Clean Workspace
clear variables
close all
clc

%% Python Must be included in path when running at Imperial the first time only
% pyversion 'O:\\python.exe';

%% Course Generation
generate_random_course=0;
%Specify Course Number for non-random input
course=1;
flag=0;

%% Generate Random Course or specify fixed csv input
% Random
if(generate_random_course==1)
flag=py.create_csv_course.produce_fn();
course=1;
while(flag~=2)
flag=flag;
end
filename='course_.csv';
else
% Custom Course
filename=strcat('courses/my_course',int2str(course),'.csv'); 
end
[obstacles,targets]=getCourseFromCSV(filename);

%% Solve Course
% Timing Should Start Here 
tic
waypoints_list= py.solve_course_pls.find_result(filename);

%% Provide Inputs to Software Model
% Convert python list to matlab datastruct
total_waypoints=length(waypoints_list);
waypoints_cell=cell(waypoints_list);
xwaypoints_cell=cell(total_waypoints,1);
ywaypoints_cell=cell(total_waypoints,1);
tags_cell=cell(total_waypoints,1);

for i=1:total_waypoints
	  xwaypoints_cell{i}=waypoints_cell{i}{1};
    ywaypoints_cell{i}=waypoints_cell{i}{2};
		tags_cell{i}=waypoints_cell{i}{3};
	  xwaypoints(i)=double(xwaypoints_cell{i})/100;
	  ywaypoints(i)=double(ywaypoints_cell{i})/100;
		tags(i)=double(tags_cell{i});
end
solve_time=toc;

%% Models Run Section: Comment out what you don't need (Software Model Or Crane Run

start_course=1;

%% Run Crane
% crane_DevDriv
% modelName='crane_DevDriv_2016a';
% modelName='crane_DevDriv_2016a';
% set_param(modelName,'StopTime','inf');
% set_param(modelName,'SimulationCommand','Update','SimulationCommand','start')
% while(start_course==1)
% 	if(get_param('hardware_DevDriv','SimulationStatus')=='running')
% 		start_course=0;
% 	end
% end
% 

%% Run Software Model
% Software Setup
software_setup;
% Run 
modelname='software_model_2016a';
simout= sim(modelname,'FixedStep',num2str(Ts),'ReturnWorkspaceOutputs','on');

%% Score Computation
% Indicate Whether a Plot is desired
showPlot='on';

% %Crane Score
% [score, tarN, obsN, payloadX, payloadY, alphaX, alphaY] = ...
%     getCrane_Score(obstacles, targets,xpos,ypos,anglex,angley,xwaypoints,ywaypoints, course, showPlot,solve_time);

%Software Model Score
[score, tarN, obsN, payloadX, payloadY, alphaX, alphaY] = ...
getSoftware_Score(simout, obstacles, targets,xwaypoints,ywaypoints,course, showPlot,solve_time);
