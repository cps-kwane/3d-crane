
targets=[47,3;47,47;3,47;5,5;35,5;35,35;5,35;23,23;4,4];
obstacles=[];
%% generate path
xwaypoints = targets(:, 1) / 100;
ywaypoints = targets(:, 2) / 100;
index = 1;
total_waypoints = length(xwaypoints);
i=1
START_COURSE = 1;

%% Run
% Setup the model name
modelName = 'high_level_v2';

% Run the simulation
simout = sim(modelName, 'FixedStep', num2str(Ts), 'ReturnWorkspaceOutputs', 'on');

% Get simulation output score
[mscore, tarN, obsN, payloadX, payloadY, alphaX, alphaY] = ...
  simple_getScore(simout, obstacles, targets,i,'on');
