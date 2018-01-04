function [xwaypoints, ywaypoints] = obtain_waypoints()

%% Set this to 1 for random course generation
generate_random_course=0;
course=3;
flag=0;

%% Python Must be included in path when running at Imperial
% pyversion 'O:\\python.exe';


%% Generate Random Course or specify fixed csv input
% Random
if (generate_random_course==1)
    flag = py.create_csv_course.produce_fn();
    course = 1;
    % while (flag~=2)
    %     flag = flag;
    % end
    filename = 'course_.csv';
else
    % Custom Course
    % filename='my_course.csv';
    filename = strcat('samples/my_course',int2str(course),'.csv'); 
end

%% Solve Course
waypoints_list= py.solve_course_pls.find_result(filename);
[obstacles,targets]=getCourseFromCSV(filename);

%% Provide Inputs to Software Model
% Convert python list to matlab datastruct
total_waypoints=length(waypoints_list);
waypoints_cell=cell(waypoints_list);
xwaypoints_cell=cell(total_waypoints,1);
ywaypoints_cell=cell(total_waypoints,1);
tags_cell=cell(total_waypoints,1);
%%disp(waypoints_cell);
for i=1:total_waypoints
	  xwaypoints_cell{i}=waypoints_cell{i}{1};
    ywaypoints_cell{i}=waypoints_cell{i}{2};
		tags_cell{i}=waypoints_cell{i}{3};
	  xwaypoints(i)=double(xwaypoints_cell{i})/100;
	  ywaypoints(i)=double(ywaypoints_cell{i})/100;
		tags(i)=double(tags_cell{i});
end

end


