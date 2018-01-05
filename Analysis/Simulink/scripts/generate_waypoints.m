function [xwaypoints, ywaypoints] = generate_waypoints(course_file)
% GENERATE_WAYPOINTS generate waypoints from given obstacles and targets.

waypoints_list = py.solve_course_pls.find_result(course_file);

%% Provide Inputs to Software Model
% Convert python list to matlab datastruct
total_waypoints = length(waypoints_list);
waypoints_cell = cell(waypoints_list);
xwaypoints_cell = cell(total_waypoints,1);
ywaypoints_cell = cell(total_waypoints,1);
tags_cell = cell(total_waypoints,1);

xwaypoints = zeros(size(waypoints_list));
ywaypoints = zeros(size(waypoints_list));
tags = zeros(size(waypoints_list));

for i=1:total_waypoints
    xwaypoints_cell{i} = waypoints_cell{i}{1};
    ywaypoints_cell{i} = waypoints_cell{i}{2};
    tags_cell{i} = waypoints_cell{i}{3};
	xwaypoints(i) = double(xwaypoints_cell{i}) / 100;
	ywaypoints(i) = double(ywaypoints_cell{i}) / 100;
    tags(i) = double(tags_cell{i});
end

end
