#include <stdio.h>
#include <stdlib.h>

const size_t SIZE = 9;
const size_t MAIN_SIZE = 3;

void PRINT_MATRIX(int ****arr,size_t SUB_SIZE);
void ASSIGN_MATRIX(int ****destArray,int **data_array);
int sudoku_solver(int **arr,size_t row,size_t col);
int IS_VALID(int **arr, size_t row, size_t col, int num);



int main() {
    size_t i,j,k,h;
    int ****MAIN_ARR = NULL;
    int **INPUT_ARR = NULL;

    MAIN_ARR = malloc(MAIN_SIZE * sizeof(int***));
    for (i = 0; i < MAIN_SIZE; i++) {
        MAIN_ARR[i] = malloc(MAIN_SIZE * sizeof(int**));
        for (j = 0; j < MAIN_SIZE; j++) {
            MAIN_ARR[i][j] = malloc(MAIN_SIZE * sizeof(int*));
            for (k = 0; k < MAIN_SIZE; k++) {
                MAIN_ARR[i][j][k] = malloc(MAIN_SIZE * sizeof(int));
            }
        }
    }


    for ( i = 0; i < MAIN_SIZE; i++) {
        for (j = 0; j < MAIN_SIZE; j++) {
            for (k = 0; k < MAIN_SIZE; k++) {
                for (h = 0; h < MAIN_SIZE;h++){
                    MAIN_ARR[i][j][k][h] = 0;
                }
            }
        }
    }


    INPUT_ARR = malloc(SIZE * sizeof(int*));
    for (i = 0; i < SIZE; i++) {
        INPUT_ARR[i] = malloc(SIZE * sizeof(int));
    }

    for ( i = 0; i < SIZE; i++) {
        for ( j = 0; j < SIZE; j++) {
            char temp;
            do {
                scanf("%c", &temp);
            } while (temp == ' ' || temp == '\n');
            INPUT_ARR[i][j] = temp - '0';
        }
    }
    printf("\n");
    ASSIGN_MATRIX(MAIN_ARR,INPUT_ARR);
    PRINT_MATRIX(MAIN_ARR, MAIN_SIZE);
    char _ = '-';
    for (i = 0; i < 31;i++){
        printf("%c",_);
    }
    printf("\n");
    sudoku_solver(INPUT_ARR,0,0);
    ASSIGN_MATRIX(MAIN_ARR,INPUT_ARR);
    printf("\n");
    PRINT_MATRIX(MAIN_ARR, MAIN_SIZE);

    for (i = 0; i < SIZE; i++){
        free(INPUT_ARR[i]);
    }
    free(INPUT_ARR);

    for (i = 0; i < MAIN_SIZE; i++) {
        for (j = 0; j < MAIN_SIZE; j++) {
            for (k = 0; k < MAIN_SIZE; k++) {
                free(MAIN_ARR[i][j][k]);
            }
            free(MAIN_ARR[i][j]);
        }
        free(MAIN_ARR[i]);
    }
    free(MAIN_ARR);
    return 0;
}

void PRINT_MATRIX(int ****arr,size_t SUB_SIZE){
    size_t i,j,k,h;
    for ( i = 0; i < SUB_SIZE; i++) {
        for ( j = 0; j < SUB_SIZE; j++) {
            for ( k = 0; k < SUB_SIZE; k++) {
              if (k == 0){
                printf(" ");
              }
                for (h = 0 ; h < SUB_SIZE;h++){
                        printf(" %d ",arr[i][j][k][h]);
                }
              printf(" ");
            }
            printf("\n");
        }
        printf("\n");
    }
}
void ASSIGN_MATRIX(int ****destArray, int **data_array) {
    size_t i,j,k,h;
    for (i = 0; i < MAIN_SIZE; i++) {
        for (j = 0; j < MAIN_SIZE; j++) {
            for (k = 0; k < MAIN_SIZE; k++) {
                for (h = 0; h < MAIN_SIZE; h++) {
                    destArray[i][j][k][h] = data_array[i * MAIN_SIZE + j][k * MAIN_SIZE + h];
                }
            }
        }   
    }
}

int IS_VALID(int **arr,size_t row,size_t col,int num) {
    size_t i,j;
    //Check row
    for (i = 0 ; i < SIZE; i++) {
            if (arr[row][i] == num){
                return 0;
            }
    }
    // Check Column
    for (i = 0; i < SIZE; i++) {
        if (arr[i][col] == num && i != row) {
            return 0;
        }
    }
    // Check grid
    size_t CURRENT_GRID_ROW = row - (row % 3) ;
    size_t CURRENT_GRID_COLUMN = col - (col % 3);
    for (i = 0 ; i < MAIN_SIZE;i++){
        for (j = 0; j < MAIN_SIZE;j++){
            if (arr[i + CURRENT_GRID_ROW][j + CURRENT_GRID_COLUMN] == num){
                return 0;
            }
        }
    }
    return 1;
}

int sudoku_solver(int **arr,size_t row,size_t col) {
    size_t i;
    if (row == SIZE - 1 && col == SIZE){
        return 1;
    }
    if (col == SIZE){
        row++;
        col=0;
    }
    if (arr[row][col] > 0){
        return sudoku_solver(arr,row,col + 1);
    }
    for (i = 1; i <= SIZE; i++) {
        if (IS_VALID(arr, row, col, i)) {
            arr[row][col] = i;
            if (sudoku_solver(arr, row, col + 1)) {
                return 1;
            }
            arr[row][col] = 0; 
        }
    }
    return 0;
}