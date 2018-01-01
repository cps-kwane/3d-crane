%% Setup
% setup model
setup;

NUM_TESTS = 10;
NUM_OBSTACLES = 0;
RANDOM_START = 1;
RANGE = [3, 47];

fprintf("Number of tests: %d\n", NUM_TESTS);
fprintf("Start!\n");

targetsReached = 0;
obstaclesHitted = 0;
hitObsTests = zeros(NUM_TESTS);
outOfBorder = zeros(NUM_TESTS, 1);
outOfAngles = zeros(NUM_TESTS, 1);

allTargets = zeros(NUM_TESTS, 2);
allZeros = zeros(NUM_TESTS, 2);
times = zeros(1, NUM_TESTS);
scores = zeros(1, NUM_TESTS);
payloadXs = {};
payloadYs = {};
alphaXs = {};
alphaYs = {};

for i = 1:NUM_TESTS
    fprintf("Running test #%4d ... ", i);
    if RANDOM_START
      xZero = randi(RANGE);
      yZero = randi(RANGE);
    end
    allZeros(i, 1) = xZero;
    allZeros(i, 2) = yZero;
    
    while 1
      x = randi(RANGE);
      y = randi(RANGE);
      
      if not (abs(x - xZero) < 3 && abs(y - yZero) < 3)
        break;
      end
    end
    
    fprintf("(%3d, %3d) -> (%3d, %3d) ", xZero, yZero, x, y);
    xZero = xZero / 100;
    yZero = yZero / 100;
    
    % setup the current run
    targets = [x, y];
    allTargets(i, 1) = x;
    allTargets(i, 2) = y;

    obstacles = generate_obstacles(NUM_OBSTACLES, RANGE, targets, 3, 'off');

    tic;
    run;
    times(i) = toc;
    scores(i) = mscore;
    
    payloadXs{i} = payloadX;
    payloadYs{i} = payloadY;
    alphaXs{i} = alphaX;
    alphaYs{i} = alphaY;

    % check out of border
    outOfBorder(i) = sum(payloadX < .03 | payloadY < .03 | ...
                         payloadX > .47 | payloadY > .47) ~= ...
                     0;
    outOfAngles(i) = sum(abs(alphaX) < 5e-3 & abs(alphaY) < 5e-3) ...
                     ~= size(alphaX, 1);
    
    % Updated targets reached
    targetsReached = targetsReached + tarN;
    
    obstaclesHitted = obstaclesHitted + obsN;
    
    hit = '';
    if obsN > 0
      hit = 'Hit';
    end

    fprintf("Score: %10.6f Time %f s %s\n", scores(i), times(i), hit);
end

fprintf("Done!\n");

fprintf("Total runtime:              %.2f s\n", sum(times));
fprintf("Average runtime:            %.2f s\n", mean(times));
fprintf("Maximum runtime:            %.2f s\n", max(times));
fprintf("Average score:              %.2f\n", mean(scores));
fprintf("Maximum score:              %.2f\n", max(scores));
fprintf("Out of border percentage:   %.2f%%\n", sum(outOfBorder) / NUM_TESTS * 100);
fprintf("Out of angle percentage:    %.2f%%\n", sum(outOfAngles) / NUM_TESTS * 100);
fprintf("Targets reached percentage: %.2f%%\n", targetsReached / NUM_TESTS * 100);
fprintf("Obstacles hit percentage:   %.2f%%\n", obstaclesHitted / NUM_TESTS * 100);

f = figure;
hold on;

scatter(allTargets(:, 1), allTargets(:, 2), 'x', 'Red');
scatter(allZeros(:, 1), allZeros(:, 2), 'x', 'Blue');
for i = 1:NUM_TESTS
  plot(payloadXs{i} * 100, payloadYs{i} * 100, 'c');
end

title(sprintf('Tested Targets %d Targets %.2f%% Obstacles %.2f%%',...
              NUM_TESTS, ...
              targetsReached / NUM_TESTS * 100, ...
              obstaclesHitted / NUM_TESTS * 100));
xlim([0 50]);
ylim([0 50]);
hold off;

print(f, 'tested_targets', '-djpeg');