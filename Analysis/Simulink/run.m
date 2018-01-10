%% generate path
tic;
[xwaypoints, ywaypoints] = generate_waypoints(course_filename);
% plot(xwaypoints, ywaypoints);
solve_time = toc;

%% Setup simulation
course = 1;
total_waypoints = length(xwaypoints);
start_course = 1;

%% Run
% Setup the model name
model_name = MODEL_NAME;
% model_name = '../../CPS_Crane_2018/software_model.slx';

% Run the simulation
simout = sim(model_name, 'FixedStep', num2str(Ts), 'ReturnWorkspaceOutputs', 'on');

% Get simulation output score
[mscore, tarN, obsN, payloadX, payloadY, alphaX, alphaY] = ...
  getSoftware_Score(simout, obstacles, targets, xwaypoints, ywaypoints,...
  course, 'off', solve_time);
