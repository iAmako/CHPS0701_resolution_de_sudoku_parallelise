#ifndef SUDOKU_H
#define SUDOKU_H
//sudoku découpé en 3 matrices ou une matrice 3D, lignes & colonnes & cases (3x3)

//char[9][9][9] = un sudoku ? 



typedef struct sudoku_s{
    int block_length;
    int array_length;
    char** sudoku_array;
    char** sudoku_blocks;
}sudoku;
typedef struct solution_s{
    float cout;
    float temperature;
    sudoku sudoku_origine;
    sudoku sudoku_solution;
}solution;



void load_sudoku(FILE* file, sudoku* sudoku_ptr);//ou à partir du char* filename ? 
void temperature(sudoku* sudoku_ptr);
void cost(sudoku* sudoku_ptr);
void new_solution(sudoku* sudoku_ptr);
#endif 