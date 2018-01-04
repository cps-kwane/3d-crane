%% Set this to 1 for random course generation
generate_random_course=0;
course=1;
flag=0;

%% Python Must be included in path when running at Imperial
%pyversion 'O:\\python.exe';
if count(py.sys.path,'') == 0
    insert(py.sys.path,int32(0),'');
end

%% Generate Random Course or specify fixed csv input
% Random
if(generate_random_course==1)
flag=py.create_csv_course.produce_fn();
course=0;
while(flag~=2)
flag=flag
end
filename='course_.csv';
else
% Custom Course
%filename='my_course.csv';
filename=strcat('courses/my_course',int2str(course),'.csv'); 
end

%% Solve Course
waypoints_list= py.solve_course_csv.find_result(filename);

