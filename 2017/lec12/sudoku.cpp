#include <cassert>
#include <iostream>
#include <vector>

#define assertm(exp, msg) assert(((void)msg, exp))

void renderBoard(std::vector<std::vector<char>> &board) {
  std::cout << std::endl;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      std::cout << board[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void renderBoardLC(std::vector<std::vector<char>> &board) {
  std::cout << "[";
  for (int i = 0; i < 9; i++) {
    std::cout << "[";
    for (int j = 0; j < 9; j++) {
      std::cout << "\"" << board[i][j] << "\"";
      if (j != 8) {
        std::cout << ",";
      }
    }
    std::cout << "]";
    if (i != 8) {
      std::cout << ",";
    }
  }
  std::cout << "]";
}

bool findEmptyCell(std::vector<std::vector<char>> &board, int &rowIdx,
                   int &colIdx) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j] == '.') {
        rowIdx = i;
        colIdx = j;
        return true;
      }
    }
  }

  return false;
}

void getSquareInitialIndexesByCell(int rowIdx, int colIdx, int &rowInitialIdx,
                                   int &colInitialIdx) {
  if (rowIdx < 3) {
    if (colIdx < 3) {
      rowInitialIdx = 0;
      colInitialIdx = 0;
    } else if (colIdx < 6) {
      rowInitialIdx = 0;
      colInitialIdx = 3;
    } else if (colIdx < 9) {
      rowInitialIdx = 0;
      colInitialIdx = 6;
    }
  } else if (rowIdx < 6) {
    if (colIdx < 3) {
      rowInitialIdx = 3;
      colInitialIdx = 0;
    } else if (colIdx < 6) {
      rowInitialIdx = 3;
      colInitialIdx = 3;
    } else if (colIdx < 9) {
      rowInitialIdx = 3;
      colInitialIdx = 6;
    }
  } else if (rowIdx < 9) {
    if (colIdx < 3) {
      rowInitialIdx = 6;
      colInitialIdx = 0;
    } else if (colIdx < 6) {
      rowInitialIdx = 6;
      colInitialIdx = 3;
    } else if (colIdx < 9) {
      rowInitialIdx = 6;
      colInitialIdx = 6;
    }
  }
}

bool isValidCell(std::vector<std::vector<char>> &board, int rowIdx, int colIdx,
                 char d) {

  for (int i = 0; i < 9; i++) {
    if (board[i][colIdx] == d) {
      return false;
    }
    if (board[rowIdx][i] == d) {
      return false;
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int rowInitialIdx, colInitialIdx;

      getSquareInitialIndexesByCell(rowIdx, colIdx, rowInitialIdx,
                                    colInitialIdx);

      if (board[rowInitialIdx + i][colInitialIdx + j] == d) {
        return false;
      }
    }
  }

  return true;
}

bool solveSudoku(std::vector<std::vector<char>> &board) {
  int rowIdx, colIdx;

  if (!findEmptyCell(board, rowIdx, colIdx)) {
    renderBoardLC(board);
    return true;
  }

  for (int d = 1; d <= 9; d++) {
    char dChar = '0' + d;
    if (isValidCell(board, rowIdx, colIdx, dChar)) {
      board[rowIdx][colIdx] = dChar;

      if (solveSudoku(board)) {
        return true;
      }

      board[rowIdx][colIdx] = '.';
    }
  }

  return false;
}

int main() {

  std::vector<std::vector<char>> board{
      {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  // renderBoard(board);

  // // testing getSquareInitialIndexesByCell
  // for (int i = 0; i < 9; i++) {
  //   for (int j = 0; j < 9; j++) {
  //     int rowInitialIdx, colInitialIdx;
  //     getSquareInitialIndexesByCell(i, j, rowInitialIdx, colInitialIdx);
  //     std::cout << rowInitialIdx << "," << colInitialIdx << " ";
  //   }
  //   std::cout << std::endl;
  // }

  // // testing isValidCell
  // assertm(isValidCell(board, 0, 2, '3') == false,
  //         "it should check the digits in the row");
  // assertm(isValidCell(board, 0, 3, '4') == false,
  //         "it should check the digits in the column");
  // assertm(isValidCell(board, 0, 2, '9') == false,
  //         "it should check the digits in the square");
  // assertm(isValidCell(board, 0, 2, '4') == true,
  //         "it should check the valid digits in the square");

  solveSudoku(board);

  return 0;
}
