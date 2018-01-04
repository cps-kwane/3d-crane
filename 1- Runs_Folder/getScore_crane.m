function [score, tarN, obsN, payloadX, payloadY, alphaX, alphaY] = ...
    getScore(obstacles, targets,xpos,ypos,anglex,angley,xpoints,ypoints, j, showPlot)
timeV=xpos.time;
cartX = xpos.signals.values;
cartY = ypos.signals.values;
alphaX =anglex.signals.values;
alphaY =angley.signals.values;

%% Calculate payload trajectory
payloadX = cartX + 0.3 * sin(alphaX);
payloadY = cartY + 0.3 * sin(alphaY);

%% Plot stuff if desired
delta = 0.01;

fig = figure;
set(fig, 'Visible', showPlot);

%% Plot stuff if desired
    delta = 0.01;
    hold off
    fig=plot(payloadX, payloadY,'m')
		title('SimScape Model')
    hold on
    for i = 1:size(targets,1)            
        rectangle('Position',[targets(i,1)/100-delta targets(i,2)/100-delta 2*delta 2*delta])
    end
    for i = 1:size(obstacles,1)
        delta = 0.01;
        rectangle('Position',[obstacles(i,1)/100-delta obstacles(i,2)/100-delta 2*delta 2*delta],'FaceColor','red')
		end	
		plot(xpoints,ypoints,'--ks',...
    'LineWidth',1,...
    'MarkerSize',5,...
    'MarkerEdgeColor','b')
	%,...)
    %'MarkerFaceColor',[0.5,0.5,0.5])
	
		%file_name = sprintf('courses/course_#%d.fig',j);
		%saveas(fig,file_name);
    
    
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
tarN
obsN
title(sprintf('Course #%d, Score %f', j, score));

end