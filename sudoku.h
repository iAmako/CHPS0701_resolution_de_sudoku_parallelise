#ifndef SUDOKU_H
#define SUDOKU_H
#include <stdio.h>
//sudoku découpé en 3 matrices ou une matrice 3D, lignes & colonnes & cases (3x3)

typedef struct sudoku_s{
    //int block_length;
    int sudoku_length;
    char** sudoku_array;
    char** sudoku_blocks;

    //correspondance array blocks : > int k = i / sudoku_length * sudoku_length; k < j / sudoku_length * sudoku_length + sudoku_length


}sudoku;

/*
//probablement useless
typedef struct solution_s{
    float cout;
    float temperature;
    sudoku sudoku_origine;
    sudoku sudoku_solution;
}solution;
*/
//charge un sudoku en mémoire, un sudoku est représenté par une ligne dans un fichier "." 
sudoku* load_sudoku(char* filename, int line_number);//ou à partir du char* filename ? 
//indique le nombre de violation de règle pour la case spécifiée en paramètres
unsigned int case_cost(sudoku *sudoku_ptr, int i, int j);
//indique le nombre de violation de règle pour la grille 
unsigned int grid_cost(sudoku *sudoku_ptr);
//génère une solution aléatoire pour le sudoku
sudoku* new_solution(sudoku* sudoku_ptr);
//libérer la mémoire
void free_sudoku(sudoku* sudoku_ptr);
//donne les coordonnées dans le tableau de blocs correspondant aux coords du tableau de lignes/colonnes  
void block_coords(int row, int col, int sudoku_length, int* coords);
//donne le numéro de bloc corresopndant aux ligne/col passé en paramètres dépendant la taille du sudoku
int block_nb(int row, int col, int sudoku_length);
//donne la position (entre 0 et 8) d'une case dans un bloc de la grille 
int pos_in_block(int row, int col, int sudoku_length);
//Affiche le sudoku passé en paramètre à l'écran
void print_sudoku(sudoku* su); 
#endif 