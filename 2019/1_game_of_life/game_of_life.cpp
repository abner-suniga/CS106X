#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

using namespace std;

void displayGrid(vector<vector<int>> &grid) {
  cout << u8"\033[2J\033[1;1H";

  for (vector<int> row : grid) {
    for (int cell : row) {
      if (cell != 0) {
        cout << "O ";
      } else {
        cout << "  ";
      }
    }
    cout << endl;
  }

  cout << endl;
  this_thread::sleep_for(chrono::milliseconds(250));
}

int isValidCell(vector<vector<int>> &grid, int row, int column) {
  return row > -1 && column > -1 && row < grid.size() &&
         column < grid[0].size();
}

int calculateNeighbors(vector<vector<int>> &grid, int row, int column) {
  int neighborsCount = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) {
        continue;
      }
      if (isValidCell(grid, row + i, column + j)) {
        if (grid[row + i][column + j] != 0) {
          neighborsCount++;
        }
      }
    }
  }
  return neighborsCount;
}

void updateGrid(vector<vector<int>> &grid, vector<vector<int>> &newGrid) {
  int numberOfNeightbors = -1;
  for (int row = 0; row < grid.size(); row++) {
    for (int column = 0; column < grid[0].size(); column++) {
      numberOfNeightbors = calculateNeighbors(grid, row, column);
      if (numberOfNeightbors <= 1) {
        newGrid[row][column] = 0;
      } else if (numberOfNeightbors == 2) {
        if (grid[row][column] == 0) {
          newGrid[row][column] = grid[row][column];
        } else {
          newGrid[row][column] = grid[row][column] + 1;
        }
      } else if (numberOfNeightbors == 3) {
        if (grid[row][column] == 0) {
          newGrid[row][column] = 1;
        } else {
          newGrid[row][column] = grid[row][column] + 1;
        }
      } else if (numberOfNeightbors >= 4) {
        newGrid[row][column] = 0;
      }
    }
  }
}

void initRandomGrid(vector<vector<int>> &grid, int MAX_AGE) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distr(1, MAX_AGE);
  uniform_int_distribution<> bin(0, 1);

  for (int row = 0; row < grid.size(); row++) {
    for (int column = 0; column < grid[0].size(); column++) {
      if (bin(gen) == 1) {
        grid[row][column] = distr(gen);
      } else {
        grid[row][column] = 0;
      }
    }
  }
}

bool isGridStable(vector<vector<int>> &grid, vector<vector<int>> &newGrid,
                  int MAX_AGE) {
  for (int row = 0; row < grid.size(); row++) {
    for (int column = 0; column < grid[0].size(); column++) {
      if ((grid[row][column] > 0 && newGrid[row][column] == 0) ||
          grid[row][column] == 0 && newGrid[row][column] > 0) {
        return false;
      }
      if (newGrid[row][column] != 0 && newGrid[row][column] < MAX_AGE) {
        return false;
      }
    }
  }

  return true;
}

void gameOfLifeLoop(vector<vector<int>> &grid, vector<vector<int>> &newGrid,
                    int MAX_AGE) {
  do {
    grid = newGrid;

    displayGrid(grid);

    updateGrid(grid, newGrid);

  } while (!isGridStable(grid, newGrid, MAX_AGE));
}

int main(int argc, char *argv[]) {

  int MAX_AGE = 100;
  int MAX_ROWS = 40;
  int MAX_COLUMNS = 40;

  if (argc == 2) {
    ifstream file;
    file.open(argv[1]);

    string line;
    while (getline(file, line)) {
      if (line.at(0) != '#') {
        break;
      }
    }

    MAX_ROWS = stoi(line);
    getline(file, line);
    MAX_COLUMNS = stoi(line);

    vector<int> gridLine(MAX_COLUMNS, 0);
    vector<vector<int>> grid(MAX_ROWS, gridLine);
    vector<vector<int>> newGrid(MAX_ROWS, gridLine);

    int row = 0;
    while (getline(file, line)) {
      for (int col = 0; col < line.length(); col++) {
        if (line[col] == 'X') {
          grid[row][col] = 1;
          newGrid[row][col] = 1;
        }
      }
      row++;
    }

    file.close();

    gameOfLifeLoop(grid, newGrid, MAX_AGE);

  } else {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(40, 60);

    MAX_ROWS = distr(gen);
    MAX_COLUMNS = distr(gen);

    vector<int> gridLine(MAX_COLUMNS, 0);
    vector<vector<int>> grid(MAX_ROWS, gridLine);
    vector<vector<int>> newGrid(MAX_ROWS, gridLine);

    initRandomGrid(grid, MAX_AGE);
    initRandomGrid(newGrid, MAX_AGE);

    gameOfLifeLoop(grid, newGrid, MAX_AGE);
  }

  return 0;
}
