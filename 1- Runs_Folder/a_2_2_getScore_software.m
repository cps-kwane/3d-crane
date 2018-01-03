%% Plotting Function Parameters
showPlot='on';

%% Get List of Obstacles & Targets
[obstacles,targets]=getCourseFromCSV(filename);
[score, tarN, obsN, payloadX, payloadY, alphaX, alphaY]=getScore(simout, obstacles, targets,xwaypoints,ywaypoints,course, showPlot);