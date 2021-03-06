%% Calculate Score based on targets, obstacles, and time
function score = simple_getScore( simout, obstacles, targets, j)
    
		timeV = simout.get('tout');
    cartX = simout.get('yout').get(1).Values.Data;
    cartY = simout.get('yout').get(3).Values.Data;
    alphaX = simout.get('yout').get(5).Values.Data;
    alphaY = simout.get('yout').get(7).Values.Data;
    
    %% Calculate payload trajectory
    
    payloadX = cartX + 0.3*sin(alphaX);
    payloadY = cartY + 0.3*sin(alphaY);
		
	
    
    
    %% Plot stuff if desired
    delta = 0.01;
    hold off
    fig=plot(payloadX, payloadY,'c')
		title('D3')
    hold on
    for i = 1:size(targets,1)            
        rectangle('Position',[targets(i,1)/100-delta targets(i,2)/100 2*delta 2*delta])
    end
    for i = 1:size(obstacles,1)
        delta = 0.01;
        rectangle('Position',[obstacles(i,1)/100-delta obstacles(i,2)/100-delta 2*delta 2*delta],'FaceColor','red')
		end
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
       ind = (payloadX(:,1) <= target(1) + 0.01) & (payloadX(:,1) >= target(1) - 0.01) & (payloadY(:,1) <= target(2) + 0.01) & (payloadY(:,1) >= target(2) - 0.01);       
       
       if(sum(ind) > 0)
            tarN = tarN + 1; % Target was hit
            tReached = min(timeV(ind,1)); % The first point in time at which the target was hit       
            if(tReached >= tComplete) 
                tComplete = tReached; % The point in time at which the last target was hit
            end
       end
    end
    
    if(tarN ~= size(targets, 1))
        tComplete = tMax; % Set tComplete to tMax if not all targets were reached
    else
        tComplete = min(tComplete, tMax); % Check if time limit was reached
    end
    
    % Check how many obstacles were hit
    for i = 1:size(obstacles,1)
       obstacle = obstacles(i,:); 
       obstacle = coordsToMeters(obstacle);
       
       % Index of payload positions within the obstacle area
       ind = (payloadX(:,1) <= obstacle(1) + 0.01) & (payloadX(:,1) >= obstacle(1) - 0.01) & (payloadY(:,1) <= obstacle(2) + 0.01) & (payloadY(:,1) >= obstacle(2) - 0.01);
       
       if(sum(ind) > 0)
          obsN = obsN + 1; % Obstacle was hit
       end
    end
    
    tarN
    obsN
    tComplete
		
    % Calculate score
		s(j)=(1 + length(targets) - tarN + obsN)*tComplete;
    score = (1 + length(targets) - tarN + obsN)*tComplete
		
end