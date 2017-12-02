#include "mex.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <limits>
#include <functional>
#include <memory>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

#define DIMENSION_SIZE 50
constexpr float HEATMAP_COEFF = 1.7;
constexpr float HEURISTIC_COEFF = 0.1;

struct Coord
{
	int row, col;

	Coord() = default;
	Coord(int row, int col)
		: row(row), col(col) { }

	bool operator<(const Coord& other) const
	{
		if (row < other.row) {
			return true;
		}

		return col < other.col;
	}

	bool operator==(const Coord& other) const
	{
		return row == other.row && col == other.col;
	}
};
struct Goal
{
	size_t idx;
	Coord coord;

	Goal(size_t idx, Coord coord)
		: idx(idx), coord(std::move(coord)) { }

	bool operator<(const Goal& other) const
	{
		return idx < other.idx;
	}
};
struct AStarEntry
{
	Coord coord;
	float cost;

	AStarEntry(Coord coord, float cost)
		: coord(std::move(coord)), cost(cost) { }

	bool operator<(const AStarEntry& other) const
	{
		if (cost < other.cost) {
			return true;
		}

		return coord < other.coord;
	}
};
struct ShortestPathKey
{
	Coord start;
	Coord goal;

	ShortestPathKey(Coord start, Coord goal)
		: start(std::move(start))
		, goal(std::move(goal)) { }

	bool operator==(const ShortestPathKey& other) const
	{
		return start == other.start && goal == other.goal;
	}
};
struct ShortestPathValue
{
	float value = 0;
	std::vector<Coord> waypoints;
};

template<typename T>
void
hash_combine(std::size_t& seed, T const& key) {
	std::hash<T> hasher;
	seed ^= hasher(key) + 0x9e3779b9ul + (seed << 6) + (seed >> 2);
}
namespace std
{
	template <>
	struct hash<Coord>
	{
		size_t operator()(const Coord& c) const
		{
			size_t hash = 0;
			::hash_combine(hash, c.row);
			::hash_combine(hash, c.col);

			return hash;
		}
	};

	template <>
	struct hash<ShortestPathKey>
	{
		size_t operator()(const ShortestPathKey& k) const
		{
			size_t hash = 0;
			::hash_combine(hash, k.start);
			::hash_combine(hash, k.goal);

			return hash;
		}
	};
}

struct Grid
{
	std::unordered_map<ShortestPathKey, ShortestPathValue> shortest_paths;
	struct Node {
		Coord predecessor;
		float heatmap;
		float gscore;
		float fscore;

		char kind;
		bool visited;
	};
	Node nodes[DIMENSION_SIZE][DIMENSION_SIZE];
};

std::vector<Coord> run_path_planning(Grid& grid);
void run_a_star(const Coord& start, const Coord& goal, Grid& grid);
float distance(const Coord& lhs, const Coord& rhs);

std::vector<Coord> run_path_planning(Grid& grid)
{
	std::vector<Goal> goals;
	std::vector<Coord> obstacles;

	goals.emplace_back(0, Coord(0, 0));
	for (int r = 0; r < DIMENSION_SIZE; r++) {
		for (int c = 0; c < DIMENSION_SIZE; c++) {
			auto& node = grid.nodes[r][c];
			if (node.kind == 'o') {
				goals.emplace_back(goals.size(), Coord(r, c));
			} else if (node.kind == 'x') {
				obstacles.emplace_back(r, c);
			}
		}
	}

	// We need the maximum value to normalise the heatmap later on
	float max_value = -std::numeric_limits<float>::max();
	float min_value = std::numeric_limits<float>::max();
	for (int r = 0; r < DIMENSION_SIZE; r++) {
		for (int c = 0; c < DIMENSION_SIZE; c++) {
			float heat_value = 0;
			for (const auto& e: obstacles) {
				if (e.row == r && e.col == c) {
					continue;
				}
				int r_diff = r - e.row;
				int c_diff = c - e.col;

				heat_value += powf(r_diff * r_diff + c_diff * c_diff, -HEATMAP_COEFF / 2);
			}

			max_value = std::max(heat_value, max_value);
			min_value = std::min(heat_value, min_value);
			grid.nodes[r][c].heatmap = heat_value;
		}
	}

	// Normalise the heatmap to [0, 1] (and set the heatmap values to be
	// 1 at the obstacles)
	float diff = max_value - min_value;
	for (int r = 0; r < DIMENSION_SIZE; r++) {
		for (int c = 0; c < DIMENSION_SIZE; c++) {
			auto& node = grid.nodes[r][c];
			node.heatmap = (node.heatmap - min_value) / diff;
		}
	}
	for (const auto& e: obstacles) {
		auto& node = grid.nodes[e.row][e.col];
		node.heatmap = 1.0;
	}

	// Add (0, 0) to the beginning of our goals, then run A*
	for (size_t i = 0; i < goals.size(); i++) {
		grid.shortest_paths.emplace(std::make_pair(
				ShortestPathKey(goals[i].coord, goals[i].coord),
				ShortestPathValue()));

		for (size_t j = i + 1; j < goals.size(); j++) {
			run_a_star(goals[i].coord, goals[j].coord, grid);
		}
	}

	float best_cost = std::numeric_limits<float>::max();
	std::vector<Coord> best;
	do {
		float cost = 0;
		for (size_t i = 0; i < goals.size(); i++) {
			size_t next = (i + 1) % goals.size();
			auto& v = grid.shortest_paths[ShortestPathKey(goals[i].coord, goals[next].coord)];

			cost += v.value;
		}

		if (cost >= best_cost) {
			continue;
		}

		std::vector<Coord> current_path;
		for (size_t i = 0; i < goals.size(); i++) {
			size_t next = (i + 1) % goals.size();
			auto& v = grid.shortest_paths[ShortestPathKey(goals[i].coord, goals[next].coord)];
			current_path.insert(current_path.end(), v.waypoints.begin(), v.waypoints.end());
		}

		best_cost = cost;
		best = std::move(current_path);
	} while (std::next_permutation(goals.begin() + 1, goals.end()));

	return best;
}

void run_a_star(const Coord& start, const Coord& goal, Grid& grid)
{
	for (int r = 0; r < DIMENSION_SIZE; r++) {
		for (int c = 0; c < DIMENSION_SIZE; c++) {
			auto& node = grid.nodes[r][c];

			node.predecessor.row = -1;
			node.predecessor.col = -1;

			node.gscore = std::numeric_limits<float>::max();
			node.fscore = std::numeric_limits<float>::max();

			node.visited = false;
		}
	}

	auto& start_node = grid.nodes[start.row][start.col];

	start_node.gscore = 0;
	start_node.fscore = distance(start, goal) * (HEURISTIC_COEFF + start_node.heatmap);

	std::priority_queue<AStarEntry> queue;
	queue.emplace(start, start_node.fscore);
	while (!queue.empty()) {
		auto current = queue.top().coord;
		queue.pop();

		if (current == goal) {
			break;
		}

		auto& node = grid.nodes[current.row][current.col];
		if (node.visited) {
			continue;
		}

		for (int dr = -1; dr <= 1; dr++) {
			for (int dc = -1; dc <= 1; dc++) {
				Coord next(current.row + dr, current.col + dc);
				if (next.row < 0 || DIMENSION_SIZE <= next.row) {
					continue;
				}
				if (next.col < 0 || DIMENSION_SIZE <= next.col) {
					continue;
				}

				auto& next_node = grid.nodes[next.row][next.col];
				if (next_node.visited) {
					continue;
				}

				float total_score = node.gscore + distance(current, goal);
				if (total_score >= next_node.gscore) {
					continue;
				}

				next_node.predecessor = current;
				next_node.gscore = total_score;
				next_node.fscore = total_score + distance(current, goal) * (HEURISTIC_COEFF + node.heatmap);

				queue.emplace(next, next_node.fscore);
			}
		}
	}

	auto& goal_node = grid.nodes[goal.row][goal.col];
	ShortestPathKey key(start, goal);
	ShortestPathKey key_reverse(goal, start);
	if (goal_node.predecessor.row == -1) {
		grid.shortest_paths[key].value = std::numeric_limits<float>::max();
		grid.shortest_paths[key_reverse].value = std::numeric_limits<float>::max();
		return;
	}

	auto& v = grid.shortest_paths[key];
	auto& v_reverse = grid.shortest_paths[key];

	v.value = goal_node.gscore;
	v_reverse.value = goal_node.gscore;

	auto it = goal;
	while (!(it == start)) {
		v.waypoints.emplace_back(it);
		it = Coord(grid.nodes[it.row][it.col].predecessor);
	}
	v_reverse.waypoints.emplace_back(start);
	v.waypoints = v_reverse.waypoints;

	std::reverse(v.waypoints.begin(), v.waypoints.end());
	printf("Waypoints:\n");
	for (const auto& e: v.waypoints) {
		printf("(%d, %d)\n", e.row, e.col);
	}
}

float distance(const Coord& lhs, const Coord& rhs)
{
	int dr = lhs.row - rhs.row;
	int dc = lhs.col - rhs.col;

	return sqrtf(dr * dr + dc * dc);
}

void mexFunction(int nlhs, mxArray** plhs, int nrhs, const mxArray** prhs)
{
	if (nrhs != 1) {
		mexErrMsgIdAndTxt("PathPlanning:oneArgument",
						  "You must pass only 1 argument, the filename");
		return;
	}

	if (nlhs != 3) {
		mexErrMsgIdAndTxt("PathPlanning:oneOutput",
						  "This function must return exactly 3 outputs");
		return;
	}

	if (!mxIsChar(prhs[0])) {
		mexErrMsgIdAndTxt("PathPlanning:notCharArray",
						  "The argument you're passing must be a string");
		return;
	}

	std::unique_ptr<Grid> grid(new Grid);
	{
		// Will get deallocated at end of scope
		std::unique_ptr<char[], decltype(&mxFree)> filename(mxArrayToString(prhs[0]), &mxFree);
		std::unique_ptr<FILE, decltype(&fclose)> infile(fopen(filename.get(), "r"), &fclose);

		if (infile == nullptr) {
			mexErrMsgIdAndTxt("PathPlanning:notFound",
							  "Could not find the file with the specified filename");
			return;
		}

		for (int r = 0; r < DIMENSION_SIZE; r++) {
			for (int c = 0; c < DIMENSION_SIZE; c++) {
				grid->nodes[r][c].kind = fgetc(infile.get());
			}
			fgetc(infile.get());
		}
	}
	auto vec = run_path_planning(*grid);
	grid.reset();

	plhs[0] = mxCreateDoubleMatrix(1, 2 * vec.size(), mxREAL);
	plhs[1] = mxCreateDoubleMatrix(1, 2 * vec.size(), mxREAL);
	plhs[2] = mxCreateDoubleMatrix(1, 2 * vec.size(), mxREAL);

	double* x_arr = mxGetPr(plhs[0]);
	double* y_arr = mxGetPr(plhs[1]);
	double* t_arr = mxGetPr(plhs[2]);

	size_t idx = 0;
	for (size_t i = 0; i < vec.size(); i++) {
		x_arr[idx] = vec[i].col / (double) DIMENSION_SIZE;
		y_arr[idx] = vec[i].row / (double) DIMENSION_SIZE;

		t_arr[idx] = 5.0 * i - 0.001;
		idx++;

		x_arr[idx] = x_arr[idx - 1];
		y_arr[idx] = y_arr[idx - 1];

		t_arr[idx] = 5.0 * i;
		idx++;
	}
}
