%% generate path
xwaypoints = targets(:, 1) / 100;
ywaypoints = targets(:, 2) / 100;
index = 1;
total_waypoints = length(xwaypoints);

START_COURSE = 1;

%% Run
% Setup the model name
modelName = 'high_level';

% Run the simulation
simout = sim(modelName, 'FixedStep', num2str(Ts), 'ReturnWorkspaceOutputs', 'on');

% Get simulation output score
[mscore, tarN] = simple_getScore(simout, obstacles, targets, i, 'off');
