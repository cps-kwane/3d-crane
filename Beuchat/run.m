%% Given Setup Script
clear variables
close all
clc

%% Hardware Model Setup 
%SimscapeCrane_MPC_start;
load('Params_Simscape.mat');
load('SSmodelParams.mat');

% Load the dynamics matrices using a solution from last assignment
Ts=1/20; 
T=10;
x0=[0 0 0 0 0 0 0 0]'; % starting offset

% Refine frictiopn model
TxVisc = 49.1750;
TxCoulomb = 2.5;
TxBreak = 0;
xZero = 0;
yZero = 0.;
TyBreak = 0;
TyVisc = 47.5650;
TyCoulomb = 1.8;
% TzVisc = 92.5; % considering the mass added
TzVisc = 342; %Z friciton without contant frictional force added by the
% mass

count=0;

% for l=1:1:10
% 
% % Repeat
% for j=1:1:10

%% Get Course from CSV File
%[obstacles,targets]=getCourseFromCSV('simple_targets_only_course.csv');
%targets=[randi([3, 47]),randi([3, 47]);randi([3, 47]),randi([3,47]);randi([3, 47]),randi([3,47])];
targets=[0.0,20;40,20;47,47];
obstacles=[];

%% Generate Path
xwaypoints=targets(:,1)/100;
ywaypoints=targets(:,2)/100;
index=1;
total_waypoints=length(xwaypoints);

Ki=0.2;
Kia=20;
Kp=11.9;
Kpa=4;



Kix=0.2;
kiax=20;
Kpx=11.9;
Kpax=4;

START_COURSE=1;
modelName='high_level';
simout= sim(modelName,'FixedStep',num2str(Ts),'ReturnWorkspaceOutputs','on');
 
 mscore = simple_getScore(simout, obstacles, targets,1)
