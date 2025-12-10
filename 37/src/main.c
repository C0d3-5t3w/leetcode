#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 9
#define EMPTY '.'

// Function to print the Sudoku board
void printBoard(char board[SIZE][SIZE]) {
  printf("\n");
  for (int i = 0; i < SIZE; i++) {
    if (i % 3 == 0 && i != 0) {
      printf("------+-------+------\n");
    }
    for (int j = 0; j < SIZE; j++) {
      if (j % 3 == 0 && j != 0) {
        printf("| ");
      }
      printf("%c ", board[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

// Check if placing num at board[row][col] is valid
bool isValid(char board[SIZE][SIZE], int row, int col, char num) {
  // Check row
  for (int i = 0; i < SIZE; i++) {
    if (board[row][i] == num) {
      return false;
    }
  }

  // Check column
  for (int i = 0; i < SIZE; i++) {
    if (board[i][col] == num) {
      return false;
    }
  }

  // Check 3x3 box
  int boxRow = (row / 3) * 3;
  int boxCol = (col / 3) * 3;
  for (int i = boxRow; i < boxRow + 3; i++) {
    for (int j = boxCol; j < boxCol + 3; j++) {
      if (board[i][j] == num) {
        return false;
      }
    }
  }

  return true;
}

// Solve Sudoku using backtracking
bool solveSudoku(char board[SIZE][SIZE]) {
  for (int row = 0; row < SIZE; row++) {
    for (int col = 0; col < SIZE; col++) {
      if (board[row][col] == EMPTY) {
        for (char num = '1'; num <= '9'; num++) {
          if (isValid(board, row, col, num)) {
            board[row][col] = num;

            if (solveSudoku(board)) {
              return true;
            }

            board[row][col] = EMPTY; // Backtrack
          }
        }
        return false; // No valid number found
      }
    }
  }
  return true; // Board is complete
}

// Read Sudoku board from user input
void readBoard(char board[SIZE][SIZE]) {
  printf("Enter the Sudoku puzzle (use '.' or '0' for empty cells):\n");
  printf("Enter 9 characters per row (without spaces), 9 rows total:\n");
  printf("Example: 53..7....\n\n");

  for (int i = 0; i < SIZE; i++) {
    char line[100];
    printf("Row %d: ", i + 1);
    scanf("%s", line);

    int len = strlen(line);
    if (len < SIZE) {
      printf("Error: Row too short. Please enter exactly 9 characters.\n");
      i--;
      continue;
    }

    for (int j = 0; j < SIZE; j++) {
      if (line[j] == '0') {
        board[i][j] = EMPTY;
      } else if ((line[j] >= '1' && line[j] <= '9') || line[j] == EMPTY) {
        board[i][j] = line[j];
      } else {
        printf("Error: Invalid character '%c'. Use 1-9 or '.' for empty.\n",
               line[j]);
        i--;
        break;
      }
    }
  }
}

// Load a sample hard puzzle
void loadSamplePuzzle(char board[SIZE][SIZE]) {
  // Hard Sudoku puzzle
  char sample[SIZE][SIZE] = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                             {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                             {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                             {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                             {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                             {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                             {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                             {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                             {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  memcpy(board, sample, SIZE * SIZE * sizeof(char));
}

int main() {
  char board[SIZE][SIZE];
  int choice;

  printf("=================================\n");
  printf("   Sudoku Tool\n");
  printf("=================================\n\n");

  printf("1. Enter your own Sudoku puzzle\n");
  printf("2. Solve a sample puzzle\n");
  printf("Enter choice (1 or 2): ");
  scanf("%d", &choice);

  if (choice == 1) {
    readBoard(board);
  } else if (choice == 2) {
    loadSamplePuzzle(board);
    printf("\nSample puzzle loaded.\n");
  } else {
    printf("Invalid choice. Using sample puzzle.\n");
    loadSamplePuzzle(board);
  }

  printf("\nOriginal Puzzle:");
  printBoard(board);

  printf("Solving...\n");

  if (solveSudoku(board)) {
    printf("Solution found!");
    printBoard(board);
  } else {
    printf("No solution exists for this puzzle.\n");
  }

  return 0;
}