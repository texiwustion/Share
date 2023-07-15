#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <ctime>

struct State {
    std::vector<std::vector<int>> board;
    int emptyRow;
    int emptyCol;
    std::string move;
    std::string flatten;
    State(const std::vector<std::vector<int>>& b, int row, int col, const std::string& m, const std::string& f)
        : board(b), emptyRow(row), emptyCol(col), move(m), flatten(f) {}
};

bool isGoalState(const std::vector<std::vector<int>>& board) {
    std::vector<std::vector<int>> goal = {
        {2, 1, 8},
        {3, 0, 7},
        {4, 5, 6}
    };

    return board == goal;
}

std::vector<State> getAdjacentStates(const State& state) {
    std::vector<State> adjacentStates;
    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    std::vector<std::string> directionNames = {"⇩", "⇧", "⇨", "⇦"};

    for (int i = 0; i < 4; ++i) {
        std::pair<int, int>& direction = directions[i];
        int newRow = state.emptyRow + direction.first;
        int newCol = state.emptyCol + direction.second;

        if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
            std::vector<std::vector<int>> newBoard = state.board;
            std::string move = std::to_string(newBoard[newRow][newCol]) + directionNames[i] + '\n';
            std::swap(newBoard[state.emptyRow][state.emptyCol], newBoard[newRow][newCol]);
            std::string newFlatten = "";
            for (auto& row : newBoard) {
                for (auto x : row) {
                    newFlatten += std::to_string(x);
                }
            }
            adjacentStates.push_back(State(newBoard, newRow, newCol, state.move + move, newFlatten));
        }
    }

    return adjacentStates;
}

std::string solveNumberPuzzle(const std::vector<std::vector<int>>& initialBoard) {
    std::queue<State> q;
    std::unordered_set<std::string> visited;
    std::unordered_set<std::string> path;
    std::string flatten = "";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            flatten += initialBoard[i][j];
        }
    }

    State initialState(initialBoard, 1, 1, "", flatten);
    q.push(initialState);
    visited.insert("");

    while (!q.empty()) {
        State currState = q.front();
        q.pop();

        if (path.find(currState.flatten) != path.end()) {
            continue;
        }
        path.insert(currState.flatten);

        if (isGoalState(currState.board)) {
            return currState.move;
        }

        std::vector<State> adjacentStates = getAdjacentStates(currState);
        for (const auto& nextState : adjacentStates) {
            if (visited.find(nextState.move) == visited.end()) {
                q.push(nextState);
                visited.insert(nextState.move);
            }
        }
    }

    return "无解";
}

int main() {
    int tt = clock();
    std::vector<std::vector<int>> initialBoard = {
        {8, 3, 2},
        {7, 0, 4},
        {5, 6, 1}
    };

    std::string solution = solveNumberPuzzle(initialBoard);
    std::cout << solution << std::endl;
    std::cout << "TIME: " << clock() - tt << std::endl;
    return 0;
}