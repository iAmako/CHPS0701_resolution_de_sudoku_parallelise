#ifndef SUDOKU_H
#define SUDOKU_H
#include <stdio.h>
//sudoku découpé en 3 matrices ou une matrice 3D, lignes & colonnes & cases (3x3)

typedef struct sudoku_s{
    //int block_length;
    int sudoku_length;
    char** sudoku_array;
    char** sudoku_blocks;
}sudoku;
typedef struct solution_s{
    float cout;
    float temperature;
    sudoku sudoku_origine;
    sudoku sudoku_solution;
}solution;

//charge un sudoku en mémoire, un sudoku est représenté par une ligne dans un fichier "." 
sudoku* load_sudoku(FILE* filename, int line_number);//ou à partir du char* filename ? 
//indique le nombre de violation de règle pour la grille 
void grid_cost(sudoku* sudoku_ptr, int line, int column);
//génère une solution aléatoire pour le sudoku
void new_solution(sudoku* sudoku_ptr);
//libérer la mémoire
void free_sudoku(sudoku* sudoku_ptr);
#endif 