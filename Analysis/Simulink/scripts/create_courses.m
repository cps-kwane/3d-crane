function [obstacles, targets, filename] = create_courses(course)
%CREATE_COURSES create test courses, either by a random generator or by
%loading files.

% will use a randomly generated course if the course id is 0.
if (course == 0)
    ret = py.create_csv_course.produce_fn();
    if (ret ~= 2)
        error('return code is not 2. Something should be wrong');
    end
    filename = 'course_random.csv';
else
    filename = ['samples/my_course' num2str(course) '.csv'];
end

[obstacles, targets] = getCourseFromCSV(filename);

end

