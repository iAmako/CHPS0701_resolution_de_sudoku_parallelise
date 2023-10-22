#include <stdio.h>
#include <stdlib.h>

#include "sudoku.h"
#include "sudoku_solving.h"

//#include "sudoku_solving.h"

//test allocation & libération mémoire sudoku  
void test_sudoku(char* file_path,int line_nb){
    //charge un sudoku en mémoire, un sudoku est représenté par une ligne dans un fichier "."     

    printf("%s,%d\n",file_path,line_nb);
    sudoku* my_sudoku = load_sudoku(file_path, line_nb);

    print_sudoku(my_sudoku);

    sudoku* solution = new_solution(my_sudoku);

    print_sudoku(solution);


    //indique le nombre de violation de règle pour la case spécifiée en paramètres
    //unsigned int case_cost(sudoku *sudoku_ptr, int i, int j);
    //indique le nombre de violation de règle pour la grille 
    //unsigned int grid_cost(sudoku *sudoku_ptr);
    //génère une solution aléatoire pour le sudoku
    //sudoku* new_solution(sudoku* sudoku_ptr);
    
    //libérer la mémoire
    free_sudoku(my_sudoku);
    free_sudoku(solution);

}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s file_path line_nb\n", argv[0]);
        return 1;
    }

    /*
    char file_path[128] = "";
    if(!sscanf(file_path,"%127s",argv[1])){
        printf("Error reading from the file\n");
    }
    */

    sudoku* my_sudoku = load_sudoku(argv[1], atoi(argv[2]));

    //test_sudoku(argv[1], atoi(argv[2]));
    sudoku* solution = solve_sudoku(my_sudoku);
    printf("Sudoku : \n\n");
    print_sudoku(my_sudoku);

    printf("Solution : \n\n");
    print_sudoku(solution);

    free_sudoku(my_sudoku);
    free_sudoku(solution);
    
}
