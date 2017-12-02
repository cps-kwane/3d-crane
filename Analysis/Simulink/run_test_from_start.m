%% Setup
% setup model
setup;

NUM_TESTS = 10;
RANGE = [3, 47];

fprintf("Number of tests: %d\n", NUM_TESTS);
fprintf("Start!\n");

targetsReached = 0;
times = zeros(1, NUM_TESTS);
scores = zeros(1, NUM_TESTS);

for i = 1:NUM_TESTS
    fprintf("Running test #%4d ... ", i);
    x = randi(RANGE);
    y = randi(RANGE);
    
    % setup the current run
    targets = [x, y];
    obstacles = [];

    tic;
    run;
    times(i) = toc;
    scores(i) = mscore;

    % Updated targets reached
    targetsReached = targetsReached + tarN;

    fprintf("Score: %10.6f Time %f s\n", scores(i), times(i));
end

fprintf("Done!\n");

fprintf("Total runtime:              %f s\n", sum(times));
fprintf("Average runtime:            %f s\n", mean(times));
fprintf("Average score:              %f\n", mean(scores));
fprintf("Maximum score:              %f\n", max(scores));
fprintf("Targets reached percentage: %f%%\n", targetsReached / NUM_TESTS * 100);