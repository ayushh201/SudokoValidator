#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int sudoku[9][9] = {
        {6, 2, 4, 5, 3, 9, 1, 8, 7},
        {5, 1, 9, 7, 2, 8, 6, 3, 4},
        {8, 3, 7, 6, 1, 4, 2, 9, 5},
        {1, 4, 3, 8, 6, 5, 7, 2, 9},
        {9, 5, 8, 2, 4, 7, 3, 6, 1},
        {7, 6, 2, 3, 9, 1, 4, 5, 8},
        {3, 7, 1, 9, 5, 6, 8, 4, 2},
        {4, 9, 6, 1, 8, 2, 5, 7, 3},
        {2, 8, 5, 4, 7, 3, 9, 1, 6}
};

bool check[11]; //Fix check for threads terminated with success(1) or failure(0)
int auxSquares = 2; //used to validate the threads that traverse the 3x3 squares

typedef struct {    //Helps us pass the data to the thread
    int row;
    int column;
} parameter;


pthread_t columns, row, first_square, second_square, third_square,
        fourth_square, fifth_square, sixth_square, seventh_square, eighth_square, ninth_square;
 
 
void *traverseColumn(void *parameters) {

    parameter *column = (parameter *) parameters;
    int initial_column = column->column;
    int initial_row = column->row;

    
    for (int i = initial_column; i < 9; i++) {
        int col[9] = {0}; //Column order
        for (int j = initial_row; j < 9; j++) {
            int aux = sudoku[i][j];
            if (col[aux - 1] == 0 && aux > 0) { //If position is free and the sudoko number is > 0
                col[aux - 1] = aux;     //We assign in position [a-1] the number to // e.g. col[(5-1)]=5
            } else if (aux <= 0) {
                check[0] = 0;
                printf("Sorry,there is an invalid number in column [%d].\n", j + 1);
                pthread_exit(0);
            } else {
                check[0] = 0;
                printf("Sorry, in column [%d] there is a repeated number.\n", j + 1);
                pthread_exit(0);
            }
        }
    }
    check[0] = 1;
    pthread_exit(0);    //We end the execution of thread.
}

void *traverseRow(void *parameters) {

    parameter *row = (parameter *) parameters;
    int initial_column = row->column;
    int initial_row = row->row;

    for (int i = initial_column; i < 9; i++) {
        int row[9] = {0};
        for (int j = initial_row; j < 9; j++) {
            int aux = sudoku[i][j];
            if (row[aux - 1] == 0 && aux > 0) {
                row[aux - 1] = aux;
            } else if (aux <= 0) {
                check[0] = 0;
                printf("Sorry,there is an invalid number in row [%d].\n", i+ 1);
                pthread_exit(0);
            } else {
                check[0] = 0;
                printf("Sorry, in row [%d] there is a repeated number.\n", i + 1);
                pthread_exit(0);
            }
        }
    }
    check[1] = 1;
    pthread_exit(0);
}

 void *walkSquare(void *parameters) {

    parameter *squareW = (parameter *) parameters;
    int rowInitial = squareW->row;
    int columnInitial = squareW->column;
    int square[9] = {0};

    for (int i = rowInitial; i < rowInitial + 3; ++i) {
        for (int j = columnInitial; j < columnInitial + 3; ++j) {
            int aux = sudoku[i][j];
            if (square[aux - 1] == 0 && aux > 0) {
                square[aux - 1] = aux;
            }
            else {
                check[auxSquares] = 0;
                auxSquares++;
                pthread_exit(0);
            }
        }
    }
    check[auxSquares] = 1;
    auxSquares++;
    pthread_exit(0);
}

int main() {

    //We assign (reserve) each parameter in memory verificarrowsand thus be able to pass the location of the Struct more easily with &a/*/
    parameter *checkrows = (parameter *) malloc(sizeof(parameter));
    checkrows->row = 0;
    checkrows->column = 0;

    parameter *checkcolumns = (parameter *) malloc(sizeof(parameter));
    checkcolumns->row = 0;
    checkcolumns->column = 0;

    parameter *square1 = (parameter *) malloc(sizeof(parameter));
    square1->row = 0;
    square1->column = 0;

    parameter *square2 = (parameter *) malloc(sizeof(parameter));
    square2->row = 0;
    square2->column = 3;

    parameter *square3 = (parameter *) malloc(sizeof(parameter));
    square3->row = 0;
    square3->column = 6;

    parameter *square4 = (parameter *) malloc(sizeof(parameter));
    square4->row = 3;
    square4->column = 0;

    parameter *square5 = (parameter *) malloc(sizeof(parameter));
    square5->row = 3;
    square5->column = 3;

    parameter *square6 = (parameter *) malloc(sizeof(parameter));
    square6->row = 3;
    square6->column = 6;

    parameter *square7 = (parameter *) malloc(sizeof(parameter));
    square7->row = 6;
    square7->column = 0;

    parameter *square8 = (parameter *) malloc(sizeof(parameter));
    square8->row = 6;
    square8->column = 3;

    parameter *square9 = (parameter *) malloc(sizeof(parameter));
    square9->row = 6;
    square9->column = 6;

    //We create the threads (position Thread_t, attributes: NULL, funcionaRealizar, (void *) argument to pass)
    pthread_create(&columns, NULL, traverseColumn, (void *) checkcolumns);
    pthread_create(&row, NULL, traverseRow, (void *) checkrows);
    pthread_create(&first_square, NULL, walkSquare, (void *) square1);
    pthread_create(&second_square, NULL, walkSquare, (void *) square2);
    pthread_create(&third_square, NULL, walkSquare, (void *) square3);
    pthread_create(&fourth_square, NULL, walkSquare, (void *) square4);
    pthread_create(&fifth_square, NULL, walkSquare, (void *) square5);
    pthread_create(&sixth_square, NULL, walkSquare, (void *) square6);
    pthread_create(&seventh_square, NULL, walkSquare, (void *) square7);
    pthread_create(&eighth_square, NULL, walkSquare, (void *) square8);
    pthread_create(&ninth_square, NULL, walkSquare, (void *) square9);

    /*This call causes thread 'a' to "sleep" until thread 'b' terminates.
    ---- pthread_join(pthread_t identifier of the thread we want to wait for, (void) returnStatement **). ----
    If we put something non-NULL in the "returnStatement", it will return what the child thread has returned.*/
    
    pthread_join(columns, NULL);
    pthread_join(row, NULL);
    pthread_join(first_square, NULL);
    pthread_join(second_square, NULL);
    pthread_join(third_square, NULL);
    pthread_join(fourth_square, NULL);
    pthread_join(fifth_square, NULL);
    pthread_join(sixth_square, NULL);
    pthread_join(seventh_square, NULL);
    pthread_join(eighth_square, NULL);
    pthread_join(ninth_square, NULL);

    //We loop through the check array and check if it was resolved or not
    for (int k = 0; k < 11; ++k) {
        if (!check[k]) {
            printf("\nWhoops...!!! The Sudoku was NOT solved...\n");
            exit(0);
        }
    }
    printf("\nGood!!! Congratulations, the Sudoku has been solved.\n");
    return 0;
}
