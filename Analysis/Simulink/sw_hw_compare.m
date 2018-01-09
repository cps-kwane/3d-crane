%% Comparison between software test results and hardware
% First please set the two directories for testing

clear variables;
close all;
clc;
warning('off','all');

TESTS_SW_DIR='tests_0109';
TESTS_HW_DIR='tests_0109_hw';

hw_workspace_files = dir([TESTS_HW_DIR '/*.mat'])';
num_files = size(hw_workspace_files, 2);
hw_workspace_file_names = strings(num_files);
sw_workspace_file_names = strings(num_files);

for i = 1:num_files
    test_id = extractAfter(hw_workspace_files(i).name, 'data');
    sw_workspace_file_names(i) = strcat(TESTS_SW_DIR, '/data_', test_id);
    hw_workspace_file_names(i) = strcat(TESTS_HW_DIR, '/data', test_id);
end

for i = 1:num_files
    sw_ws = load(char(sw_workspace_file_names(i)));
    hw_ws = load(char(hw_workspace_file_names(i)));
    hw_ws
    
    plot(sw_ws.payloadX, sw_ws.payloadY);
    plot(hw_ws.payloadX, hw_ws.payloadY);
end