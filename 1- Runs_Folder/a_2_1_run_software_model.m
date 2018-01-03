%% Provide Inputs to Software Model
% Convert python list to matlab datastruct
total_waypoints=length(waypoints_list);
waypoints_cell=cell(waypoints_list);
xwaypoints_cell=cell(total_waypoints,1);
ywaypoints_cell=cell(total_waypoints,1);
%%disp(waypoints_cell);
for i=1:total_waypoints
	  xwaypoints_cell{i}=waypoints_cell{i}{1};
    ywaypoints_cell{i}=waypoints_cell{i}{2};
	  xwaypoints(i)=double(xwaypoints_cell{i})/100;
	  ywaypoints(i)=double(ywaypoints_cell{i})/100;
end
total_waypoints=length(xwaypoints);

%set start_course to 1
start_course=1;

%% Run Software Model
modelName='kwane_crane';
simout= sim(modelName,'FixedStep',num2str(Ts),'ReturnWorkspaceOutputs','on');

