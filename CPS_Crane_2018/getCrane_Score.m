function [score, tarN, obsN, payloadX, payloadY, alphaX, alphaY] = ...
    getCrane_Score(obstacles, targets,xpos,ypos,anglex,angley,xpoints,ypoints, course, showPlot,solve_time)

%% Payload Trajectory Computation
cartX = xpos.signals.values;
cartY = ypos.signals.values;
alphaX =anglex.signals.values;
alphaY =angley.signals.values;
timeV=xpos.time;

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
set(fig, 'Visible', showPlot);
fig=plot(payloadX, payloadY,'m')
title(sprintf('Course #%d,Crane Score %f, ttaken: %f', course, score,tComplete));
hold on;

% Plot Targets in Green
  for i = 1:size(targets,1)            
        rectangle('Position',[targets(i,1)/100-delta targets(i,2)/100-delta 2*delta 2*delta],'FaceColor','green');
	end
% Plot Obstacles in Red
    for i = 1:size(obstacles,1)
        delta = 0.01;
        rectangle('Position',[obstacles(i,1)/100-delta obstacles(i,2)/100-delta 2*delta 2*delta],'FaceColor','red')
		end
		
% Plot List of Waypoints and direct path
		plot(xpoints,ypoints,'--ks',...
    'LineWidth',1,...
    'MarkerSize',8,...
    'MarkerEdgeColor','b')
    
