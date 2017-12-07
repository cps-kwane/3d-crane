
%% Obtain waypoints through python script
% 
% %Enable Running python Script From Matlab
% % if count(py.sys.path,'') == 0
% %     insert(py.sys.path,int32(0),'');
% % end
% %Run Full Script Once to Ensure No errors
% % if(system('python -B solve_course_csv.py')==0)  %DON'T CACHE -B
% %     display('no errors')
% % end
% 
% %% Generate Random Course
% % flag=0;
% % flag=py.create_csv_course.produce_fn()
% % 
% % %while(flag~=2)
% % %	flag=flag
% % %end
% % Store points to compute score later
%[obstacles,targets]=getCourseFromCSV('course_.csv');


tic;
%waypoints_list= py.solve_course_csv.find_result('course_.csv');
% %Convert python list to matlab datastruct
% total_waypoints=length(waypoints_list);
% waypoints_cell=cell(waypoints_list);
% xwaypoints_cell=cell(total_waypoints,1);
% ywaypoints_cell=cell(total_waypoints,1);
% % disp(waypoints_cell);
% 
% for i=1:total_waypoints
% 	  xwaypoints_cell{i}=waypoints_cell{i}{1};
%     ywaypoints_cell{i}=waypoints_cell{i}{2};
% 	  xwaypoints(i)=double(xwaypoints_cell{i})/100;
% 	  ywaypoints(i)=double(ywaypoints_cell{i})/100;
% end
% % 
% xwaypoints(1)=[];
% ywaypoints(1)=[];
total_waypoints=length(xwaypoints);
% 
% 
% %% Run Simulation
% START_COURSE=1;
modelName='high_level_v2';
simout= sim(modelName,'FixedStep',num2str(Ts),'ReturnWorkspaceOutputs','on');
fprintf('time taken = %f',toc)
%mscore = simple_getScore(simout, obstacles, targets,1)
% 
% %delete('course_.csv');
% 
[mscore, tarN, obsN, payloadX, payloadY, alphaX, alphaY] = ...
  simple_getScore(simout, obstacles, targets,i,'on');

mscore
