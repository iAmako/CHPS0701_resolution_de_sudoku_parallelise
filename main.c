#include <stdio.h>
#include "sudoku.h"
//#include "sudoku_solving.h"

//test allocation & libération mémoire sudoku  
void test_sudoku(file_path,line_nb){
    //charge un sudoku en mémoire, un sudoku est représenté par une ligne dans un fichier "." 
    sudoku* my_sudoku = load_sudoku(file_path, line_nb);

    //indique le nombre de violation de règle pour la case spécifiée en paramètres
    //unsigned int case_cost(sudoku *sudoku_ptr, int i, int j);
    //indique le nombre de violation de règle pour la grille 
    //unsigned int grid_cost(sudoku *sudoku_ptr);
    //génère une solution aléatoire pour le sudoku
    //sudoku* new_solution(sudoku* sudoku_ptr);
    
    //libérer la mémoire
    void free_sudoku(my_sudoku);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s file_path line_nb\n", argv[0]);
        return 1;
    }

    char file_path[128] = argv[1];
    int line_nb = (int)argv[2];

    test_sudoku(file_path,line_nb);
}
