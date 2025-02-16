#include <stdio.h>
#include <stdlib.h>
#define N 9

// check if num can be placed in the given grid at the given position
int isLegal(int grid[N][N], int row, int col, int num) {
    // which box is row, col in - bottom right corner
    int boxR = (row / 3) * 3; // todo - factor of N
    int boxC = (col / 3) * 3;


    for (int i = 0; i < N; i++) {
        // check row

        if (grid[row][i] == num) {
            // printf("illegal by row - %d\n", i);
            return 0;
        } 

        // check column
        if (grid[i][col] == num) {
            // printf("illegal by col - %d\n", i);
            return 0;
        } 
    
    }

    // check box - todo, combine w/ above loop
    for (int i = boxR; i < boxR + 3; i++) {
        for (int j = boxC; j < boxC + 3; j++) {
            if (grid[i][j] == num) {
                // printf("illegal by box - %d,%d\n", i,j);
                return 0;
            }
        }
    }
    
    return 1;

}

int solveSudoku(int grid[N][N], int row, int col) {
    if (row >= N -1 && col >= N) {
        return 1; // all rows traversed
    }
    
    if (col >= N) {
        col = 0;
        row = row + 1;
    } 

    if (grid[row][col] != 0) {
        return solveSudoku(grid, row, col + 1);
    }
    
    for (int i = 1; i < N + 1; i++) { // digit to try
        if (!isLegal(grid, row, col, i)) {
            continue;
        }
        
        // place the digit
        grid[row][col] = i;

        if (solveSudoku(grid, row, col + 1) == 1) {
            return 1;
        } else {
            grid[row][col] = 0; // backtrack
        }
    }

    return 0;
}

// Print grid to the terminal
void print(int arr[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

int main()
{
    // 0 means unassigned cells
    int grid[N][N] = { { 5, 3, 0, 0, 7, 0, 0, 0, 0 },
                       { 6, 0, 0, 1, 9, 5, 0, 0, 0 },
                       { 0, 9, 8, 0, 0, 0, 0, 6, 0 },
                       { 8, 0, 0, 0, 6, 0, 0, 0, 3 },
                       { 4, 0, 0, 8, 0, 3, 0, 0, 1 },
                       { 7, 0, 0, 0, 2, 0, 0, 0, 6 },
                       { 0, 6, 0, 0, 0, 0, 2, 8, 0 },
                       { 0, 0, 0, 4, 1, 9, 0, 0, 5 },
                       { 0, 0, 0, 0, 8, 0, 0, 7, 0 } };

    if (solveSudoku(grid, 0, 0) == 1) {
        print(grid);
    } else {
        printf("No solution exists\n");
    }

    return 0;
}
