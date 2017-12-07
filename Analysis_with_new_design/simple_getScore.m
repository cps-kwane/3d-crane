%% Calculate Score based on targets, obstacles, and time
function [score, tarN, obsN, payloadX, payloadY, alphaX, alphaY] = ...
    simple_getScore(simout, obstacles, targets, j, showPlot)
% SIMPLE_GETSCORE get the score from simulation output and plot it if
% desired.

%% Get outputs from simout
timeV = simout.get('tout');
cartX = simout.get('yout').get(1).Values.Data;
cartY = simout.get('yout').get(3).Values.Data;
alphaX = simout.get('yout').get(5).Values.Data;
alphaY = simout.get('yout').get(7).Values.Data;

%% Calculate payload trajectory
payloadX = cartX + 0.3 * sin(alphaX);
payloadY = cartY + 0.3 * sin(alphaY);

%% Plot stuff if desired
delta = 0.01;

fig = figure;
set(fig, 'Visible', showPlot);

hold off;
% plot the course
plot(payloadX, payloadY,'c');

hold on;

% plot the final position
scatter(payloadX(size(payloadX)), payloadY(size(payloadX)), 'x', 'Red');

xlim([0 1]);
ylim([0 1]);

% Plot targets
for i = 1:size(targets,1)
    scatter(targets(i, 1), targets(i, 2), '.', 'Black');
    
    rectangle('Position', ...
        [ targets(i, 1) / 100-delta ...
          targets(i, 2) / 100-delta ...
          2 * delta ...
          2 * delta])
end

% Plot obstacles
for i = 1:size(obstacles,1)
    rectangle('Position', ...
        [ obstacles(i, 1) / 100 - delta ...
          obstacles(i, 2) / 100 - delta ...
          2*delta ...
          2*delta], 'FaceColor', 'red')
end

file_name = sprintf('courses/course_#%d', j);
print(fig, file_name, '-dpng');

%% Calculate score
tarN = 0;
obsN = 0;
tComplete = 0;
tMax = 10*60;

% Check how many targets were hit
for i = 1:size(targets,1)
  target = targets(i,:); 
  target = coordsToMeters(target);

  % Index of payload positions within the target area
  ind = (payloadX(:,1) <= target(1) + delta) & ...
        (payloadX(:,1) >= target(1) - delta) & ...
        (payloadY(:,1) <= target(2) + delta) & ...
        (payloadY(:,1) >= target(2) - delta);       

  if(sum(ind) > 0)
    % Target was hit
    tarN = tarN + 1; 
    % The first point in time at which the target was hit       
    tReached = min(timeV(ind,1)); 

    if (tReached >= tComplete)
      % The point in time at which the last target was hit
      tComplete = tReached;
    end
   end
end

if (tarN ~= size(targets, 1))
  tComplete = tMax; % Set tComplete to tMax if not all targets were reached
else
  tComplete = min(tComplete, tMax); % Check if time limit was reached
end

% Check how many obstacles were hit
for i = 1:size(obstacles,1)
  obstacle = obstacles(i,:); 
  obstacle = coordsToMeters(obstacle);

  % Index of payload positions within the obstacle area
  ind = (payloadX(:,1) <= obstacle(1) + delta) & ...
        (payloadX(:,1) >= obstacle(1) - delta) & ...
        (payloadY(:,1) <= obstacle(2) + delta) & ...
        (payloadY(:,1) >= obstacle(2) - delta);

  if(sum(ind) > 0)
    obsN = obsN + 1; % Obstacle was hit
  end
end

% Calculate score
s(j) = (1 + length(targets) - tarN + obsN) * tComplete;
score = (1 + length(targets) - tarN + obsN) * tComplete;

title(sprintf('Course #%d, Score %f', j, score));

end