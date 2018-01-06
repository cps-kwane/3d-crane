function [score, tarN, obsN, payloadX, payloadY, alphaX, alphaY] = ...
    getSoftware_Score(simout, obstacles, targets, xpoints, ypoints,...
    course, showPlot, solve_time)
	

%% Payload Trajectory Computation 
% Get outputs from simout
timeV = simout.get('tout');
cartX = simout.get('yout').get(1).Values.Data;
cartY = simout.get('yout').get(3).Values.Data;
alphaX = simout.get('yout').get(5).Values.Data;
alphaY = simout.get('yout').get(7).Values.Data;
% Calculate payload trajectory
payloadX = cartX + 0.3 * sin(alphaX);
payloadY = cartY + 0.3 * sin(alphaY);

%% Score Computation
delta = 0.01;
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
  tComplete = min(tComplete, tMax)+solve_time; % Check if time limit was reached
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
score = (1 + length(targets) - tarN + obsN) * tComplete;

%% Plotting (Comment out if not desired)
fig = figure;
hold on;
set(fig, 'Visible', showPlot);
plot(payloadX, payloadY, 'm');
title(sprintf('Course #%d, Crane Score %f, ttaken: %f',...
  course, score, tComplete));

% Plot Targets in Green
for i = 1:size(targets,1)            
  rectangle('Position',...
    [targets(i,1)/100-delta targets(i,2)/100-delta 2*delta 2*delta],...
    'FaceColor','green');
end
% Plot Obstacles in Red
for i = 1:size(obstacles,1)
  delta = 0.01;
  rectangle('Position',...
    [obstacles(i,1)/100-delta obstacles(i,2)/100-delta 2*delta 2*delta],...
    'FaceColor','red');
end
		
% Plot List of Waypoints and direct path
plot(xpoints,ypoints,'--ks',...
  'LineWidth',1,...
  'MarkerSize',8,...
  'MarkerEdgeColor','b');

