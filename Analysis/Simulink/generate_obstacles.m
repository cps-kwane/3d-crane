function [ obstacles ] = generate_obstacles( numObs, range, targets, minDist, showPlot )
%GENERATE_OBSTACLES Generate a list of obstacles.

obstacles = zeros(numObs, 2);
for i = 1:numObs
  while 1
    x = randi(range);
    y = randi(range);
    obstacles(i, 1) = x;
    obstacles(i, 2) = y;

    if size(targets) == 0
      
      break;
    end

    offsetX = abs(targets(:, 1) - x);
    offsetY = abs(targets(:, 2) - y);
   
    % obstacles should have good distances among targets
    if sum(offsetX < minDist & offsetY < minDist) == 0
      if i == 1
        break;
      end
      
      % so for other obstacles
      offsetObsX = abs(obstacles(1:i-1, 1) - x);
      offsetObsY = abs(obstacles(1:i-1, 2) - y);
      if (sum(offsetObsX < minDist & offsetObsY < minDist) == 0)
        break;
      end
    end
  end
end

fig = figure;
set(fig, 'Visible', showPlot);
hold on;
scatter(obstacles(:, 1), obstacles(:, 2), 'x', 'Red', 'DisplayName', 'obstacles');
scatter(targets(:, 1), targets(:, 2), '.', 'Blue', 'DisplayName', 'targets');
title('Generated random targets');
legend('show');
xlim([0 50]);
ylim([0 50]);
hold off;
end

