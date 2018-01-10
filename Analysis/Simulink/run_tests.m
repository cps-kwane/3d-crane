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
MODEL_NAME='high_level_v4_wo.slx';
RESULTS_DIR = 'results_0110_200_v4_wo';
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
totalTargets = 0;
totalObstacles = 0;

mkdir(RESULTS_DIR);
logFd = fopen([RESULTS_DIR '/results.log'], 'w');

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
               [RESULTS_DIR '/course_' num2str(i) '.csv']);
    end
    allTargets{i} = targets;
    allObstacles{i} = obstacles;
    totalTargets = totalTargets + size(targets, 1);
    totalObstacles = totalObstacles + size(obstacles, 1);
    
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
    miss = '';
    if obsN > 0
      hit = 'Hit';
    end
    if tarN < size(targets, 1)
      miss = 'Miss';
    end

    fprintf('Score: %10.6f Time %f s %s %s\n', scores(i), times(i), hit, miss);
    fprintf(logFd, 'Score: %10.6f Time %f s %s %s\n', scores(i), times(i), hit, miss);
    save(sprintf('%s/data_%d.mat', RESULTS_DIR, i), 'targets', 'obstacles',...
         'xwaypoints', 'ywaypoints', 'payloadX', 'payloadY',...
         'alphaX', 'alphaY', 'tarN', 'obsN');
     
    % plot
    f = figure;
    hold on;
    set(f, 'Visible', 'off');
    h = plot(payloadXs{i} * 100, payloadYs{i} * 100);
    scatter(allTargets{i}(:, 1), allTargets{i}(:, 2));
    scatter(allObstacles{i}(:, 1), allObstacles{i}(:, 2), 'x');
    for j = 1:size(targets, 1)
        rectangle('Position',...
                  [targets(j, 1) - 1, targets(j, 2) - 1,...
                   2, 2]);
    end
    for j = 1:size(obstacles, 1)
        rectangle('Position',...
                  [obstacles(j, 1) - 1, obstacles(j, 2) - 1,...
                   2, 2], 'EdgeColor', 'r');
    end
    title(sprintf('CASE %d', i));
    xlim([0 50]);
    ylim([0 50]);
    hold off;

    print(f, sprintf('%s/result_%d.jpg', RESULTS_DIR, i), '-djpeg');
end

fprintf('Done!\n');

fprintf(logFd, 'Total runtime:              %.2f s\n', sum(times));
fprintf(logFd, 'Average runtime:            %.2f s\n', mean(times));
fprintf(logFd, 'Maximum runtime:            %.2f s\n', max(times));
fprintf(logFd, 'Average score:              %.2f\n', mean(scores));
fprintf(logFd, 'Maximum score:              %.2f\n', max(scores));
fprintf(logFd, 'Out of border percentage:   %.2f%%\n', sum(outOfBorder) / NUM_TESTS * 100);
fprintf(logFd, 'Out of angle percentage:    %.2f%%\n', sum(outOfAngles) / NUM_TESTS * 100);
fprintf(logFd, 'Targets reached percentage: %.2f%%\n', targetsReached / totalTargets * 100);
fprintf(logFd, 'Obstacles hit percentage:   %.2f%%\n', obstaclesHitted / totalObstacles * 100);

fclose(logFd);


% allTargets = reshape(allTargets, NUM_TESTS * NUM_TARGETS, 2);