#include <iostream>
#include <tuple>
#include <vector>

using Board = std::vector<std::vector<char>>;

void printBoard(const Board &board) {
  for (std::vector row : board) {
    for (char item : row) {
      std::cout << item << " ";
    }
    std::cout << std::endl;
  }
}

void initBoard(Board &board) {
  for (int i = 0; i < 8; i++) {
    std::vector<char> row;
    for (int j = 0; j < 8; j++) {
      row.push_back('0');
    }
    board.push_back(row);
  }
}

bool noChoicesInBoard(const Board &board) {
  for (std::vector row : board) {
    for (char item : row) {
      if (item == '0') {
        return false;
      }
    }
  }
  return true;
}

void pickCell(Board &board, int i, int j) {
  board[i][j] = 'Q';

  // vertical
  for (int k = 0; k < 8; k++) {
    if (board[k][j] == '0') {
      board[k][j] = 'I';
    }
  }

  // horizontal
  for (int k = 0; k < 8; k++) {
    if (board[i][k] == '0') {
      board[k][j] = 'I';
    }
  }

  // diagonal
  int smaller = i <= j ? i : j;
  int s_i = i - smaller;
  int s_j = j - smaller;
  while (s_i < 8 && s_j << 8) {
    if (board[s_i][s_j] == '0') {
      board[s_i][s_j] = 'I';
    }
    s_i++;
    s_j++;
  }
}

// 00 01 02 03 04
// 10 11 12 13 14
// 20 21 22 23 24
// 30 31 32 33 23
// 40 41 42 43 44

void queens(Board board) {
  if (noChoicesInBoard(board)) {
    printBoard(board);
    return;
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[i][j] == '0') {
        // pick
      }
    }
  }
}

int main() {

  Board board;

  initBoard(board);

  printBoard(board);

  return 0;
}
