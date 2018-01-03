%% Plotting Function Parameters
showPlot='on';

%% Get List of Obstacles & Targets
[score, tarN, obsN, payloadX, payloadY, alphaX, alphaY] = ...
    getScore(obstacles, targets,xpos,ypos,anglex,angley,xwaypoints,ywaypoints,course, showPlot)