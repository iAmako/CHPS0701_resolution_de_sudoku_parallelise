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


//charge un sudoku en mémoire, un sudoku est représenté par une ligne dans un fichier "." 
void load_sudoku(FILE* file, sudoku* sudoku_ptr,int line_nb);//ou à partir du char* filename ? 
//valeur utilisé par l'algorithme pour décider de la vitesse du recuit simulé 
void temperature(sudoku* sudoku_ptr);
//indique le nombre de violation de règle pour la grille 
void cost(sudoku* sudoku_ptr);
//génère une solution aléatoire pour le sudoku
void new_solution(sudoku* sudoku_ptr);
#endif 