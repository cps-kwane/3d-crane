% Setup script for verification

%% Given Setup Script
clear variables
close all
clc

%% Crane Hardware Model Setup 
% Load hardware parameters
load('Params_Simscape.mat');
load('SSmodelParams.mat');

% Load the dynamics matrices using a solution from last assignment
Ts = 1 / 20; 
T = 10;
x0 = [0 0 0 0 0 0 0 0]'; % starting offset

% Refine friction model
TxVisc = 49.1750;
TxCoulomb = 2.5;
TxBreak = 0;
xZero = 0;
yZero = 0.;
TyBreak = 0;
TyVisc = 47.5650;
TyCoulomb = 1.8;

% considering the mass added
% TzVisc = 92.5; 
% Or Z friciton without contant frictional force added by the
% mass
TzVisc = 342; 

% PID parameters
Ki = 0.06;
Kia = -0.3;
Kp = 4.5;
Kpa = 4;

Kix = -0.08;
kiax = 13.56;
Kpx = 7.1849;
Kpax = 4.2701;
