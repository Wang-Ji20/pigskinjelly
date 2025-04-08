#include <deque>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
const int UNVISITED = 0x3f3f3f;

void
print_maze(vector<vector<char>> &maze) {
  for (auto &&maze_row : maze) {
    for (auto maze_grid : maze_row) {
      cout << maze_grid;
    }
    cout << "\n";
  }
}

struct Position {
  int x;
  int y;
};

bool
pos_eq(Position p0, Position p1) {
  return p0.x == p1.x && p0.y == p1.y;
}

const vector<Position> POSITION_UPDATES = {
    {.x = 1, .y = 0}, {.x = -1, .y = 0}, {.x = 0, .y = 1}, {.x = 0, .y = -1}};

void
print_pos(Position pos) {
  cout << '(' << pos.x << ", " << pos.y << ")\n";
}

// SOL0: flow BFS
int
flow_bfs(vector<vector<char>> &maze,
         Position start_point,
         Position goal_point) {
  auto n = maze.size();
  deque<Position> visiting;
  vector<vector<int>> turn_memo(n, vector<int>(n, UNVISITED));

  visiting.emplace_back(start_point);
  turn_memo[start_point.x][start_point.y] = -1;
  while (!visiting.empty()) {

    auto source_pos = visiting.front();
    visiting.pop_front();

    for (int direction = 0; direction < 4; direction++) {
      auto dx = POSITION_UPDATES[direction].x;
      auto dy = POSITION_UPDATES[direction].y;
      // flow extension
      auto cur_pos = source_pos;

      for (int step = 0; step < n; step++) {
        if (cur_pos.x + dx < 0 || cur_pos.x + dx >= n || cur_pos.y + dy < 0 ||
            cur_pos.y + dy >= n) {
          break;
        }

        cur_pos = {.x = cur_pos.x + dx, .y = cur_pos.y + dy};

        if (maze[cur_pos.x][cur_pos.y] == 'x') {
          break;
        }

        if (turn_memo[cur_pos.x][cur_pos.y] != UNVISITED) {
          continue;
        }

        turn_memo[cur_pos.x][cur_pos.y] =
            turn_memo[source_pos.x][source_pos.y] + 1;

        if (pos_eq(cur_pos, goal_point)) {
          return turn_memo[cur_pos.x][cur_pos.y];
        }

        visiting.push_back(cur_pos);
      }
    }
  }

  return -1;
}

// SOL1: optimized DFS

// SOL2: Dijkstra

int
main() {
  int N;
  cin >> N;

  vector<vector<char>> maze;

  Position a_pos;
  Position b_pos;

  for (int i = 0; i < N; i++) {
    vector<char> maze_line;
    for (int j = 0; j < N; j++) {
      string input;
      cin >> input;
      if (input == "A") {
        a_pos = {.x = i, .y = j};
      }

      if (input == "B") {
        b_pos = {.x = i, .y = j};
      }
      maze_line.push_back(input[0]);
    }
    maze.push_back(maze_line);
  }

  cout << flow_bfs(maze, a_pos, b_pos);

  return 0;
}
