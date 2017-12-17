generate_random_course=0;
flag=0;
%% Python Must be included in path
%pyversion 'O:\\python.exe';

%% Generate Random Course or specify fixed csv input
if(generate_random_course==1)
flag=py.create_csv_course.produce_fn();
while(flag~=2)
flag=flag
end
filename='course_.csv';
else
%% Get waypoints from fixed course
%filename='my_course.csv';
filename='my_course2.csv';
end

%% Solve Course
waypoints_list= py.solve_course_csv.find_result(filename);



%% Convert python list to matlab datastruct
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

%% Specify number of waypoints for FSM
total_waypoints=length(xwaypoints);

    





