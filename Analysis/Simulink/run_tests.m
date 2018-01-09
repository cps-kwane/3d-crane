%% This is the main script for verification of the CPS crane project.
% The test will go with 3 sections:
% 1. Generate or load test cases
% 2. Run each test case and see whether all assertions can hold
% 3. Give a summary of all cases tested

%% Setup
clear variables;
close all;
clc;
addpath('scripts');
P = py.sys.path;
if count(P, [pwd '/scripts']) ~= 1
  insert(P, int32(0), [pwd '/scripts']);
end

% setup model
software_setup;


% parameters
NUM_SAMPLES = size(dir('samples/*.csv'), 1);
NUM_RANDOM_TESTS = 100;
NUM_TESTS = NUM_SAMPLES + NUM_RANDOM_TESTS;
NUM_TARGETS = 3;
NUM_OBSTACLES = 3;
MAX_NUM_TARGETS = 10;
MAX_NUM_OBSTACLES = 10;
% RANDOM_START = 1;
% RANGE = [3, 47];

fprintf('Number of tests: %d\n', NUM_TESTS);
fprintf('Start!\n');

% statistics
targetsReached = 0;
obstaclesHitted = 0;
hitObsTests = zeros(NUM_TESTS);
outOfBorder = zeros(NUM_TESTS, 1);
outOfAngles = zeros(NUM_TESTS, 1);

allTargets = cell(NUM_TESTS);
allObstacles = cell(NUM_TESTS);
times = zeros(1, NUM_TESTS);
solveTimes = zeros(1, NUM_TESTS);
scores = zeros(1, NUM_TESTS);
payloadXs = cell(NUM_TESTS);
payloadYs = cell(NUM_TESTS);
alphaXs = cell(NUM_TESTS);
alphaYs = cell(NUM_TESTS);

%% Main Loop
for i = 1:NUM_TESTS
    fprintf('Running test #%4d ... ', i);
    
    %% Generate Courses
    if i <= NUM_SAMPLES
      course = i;
    else
      course = 0;
    end
    [obstacles, targets, course_filename] = create_courses(course);
    if course == 0
      copyfile(course_filename, ...
               ['results/course_' num2str(i - NUM_SAMPLES) '.csv']);
    end
    allTargets{i} = targets;
    allObstacles{i} = obstacles;
    
    tic;
    run;  
    times(i) = toc;
    scores(i) = mscore;
    
    payloadXs{i} = payloadX;
    payloadYs{i} = payloadY;
    alphaXs{i} = alphaX;
    alphaYs{i} = alphaY;

    % check out of border
    outOfBorder(i) = sum(payloadX < .02 | payloadY < .02 | ...
                         payloadX > .48 | payloadY > .48) ~= ...
                     0;
    outOfAngles(i) = sum(abs(alphaX) < .15 & abs(alphaY) < .15) ...
                     ~= size(alphaX, 1);
    
    % Updated targets reached
    targetsReached = targetsReached + tarN;
    
    obstaclesHitted = obstaclesHitted + obsN;
    
    hit = '';
    if obsN > 0
      hit = 'Hit';
    end

    fprintf('Score: %10.6f Time %f s %s\n', scores(i), times(i), hit);
    save(sprintf('results/data_%d.mat', i), 'targets', 'obstacles',...
         'xwaypoints', 'ywaypoints', 'payloadX', 'payloadY',...
         'alphaX', 'alphaY', 'tarN', 'obsN');
end

fprintf('Done!\n');

fprintf('Total runtime:              %.2f s\n', sum(times));
fprintf('Average runtime:            %.2f s\n', mean(times));
fprintf('Maximum runtime:            %.2f s\n', max(times));
fprintf('Average score:              %.2f\n', mean(scores));
fprintf('Maximum score:              %.2f\n', max(scores));
fprintf('Out of border percentage:   %.2f%%\n', sum(outOfBorder) / NUM_TESTS * 100);
fprintf('Out of angle percentage:    %.2f%%\n', sum(outOfAngles) / NUM_TESTS * 100);
fprintf('Targets reached percentage: %.2f%%\n', targetsReached / NUM_TESTS * 100);
fprintf('Obstacles hit percentage:   %.2f%%\n', obstaclesHitted / NUM_TESTS * 100);



% allTargets = reshape(allTargets, NUM_TESTS * NUM_TARGETS, 2);
% generate figure for each course
for i = 1:NUM_TESTS
  f = figure;
  hold on;
  set(f, 'Visible', 'off');
  h = plot(payloadXs{i} * 100, payloadYs{i} * 100);
  scatter(allTargets{i}(:, 1), allTargets{i}(:, 2));
  scatter(allObstacles{i}(:, 1), allObstacles{i}(:, 2), 'x');
  
  title(sprintf('CASE %d', i));
  xlim([0 50]);
  ylim([0 50]);
  hold off;

  print(f, sprintf('results/result_%d.jpg', i), '-djpeg');
end
