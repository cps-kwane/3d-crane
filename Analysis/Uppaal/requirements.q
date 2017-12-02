//This file was generated from (Commercial) UPPAAL 4.0.14 (rev. 5615), May 2014

/*
When path planner is finished, the crane should eventually wait the points
*/
A<> path_plan.issue_points imply main.waiting_point

/*

*/
A<> env.time_out imply (main.term and path_plan.term and controller.term)

/*

*/
A<> main.done imply (path_plan.done and controller.done and env.done)

/*
The state where all FSMs are done can be reached
*/
E<> main.done and path_plan.done and controller.done and env.done
