#include "sudoku.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>

#define TAILLE_SUDOKU 3

//charge un sudoku en mémoire, un sudoku est représenté par une ligne dans un fichier "." 
sudoku* load_sudoku(FILE* filename, int line_number){
    sudoku* new_sudoku = (sudoku*)malloc(sizeof(sudoku));
    if (new_sudoku == NULL) {
        // Gestion de l'erreur de mémoire
        return NULL;
    }

    //Ouverture du fichier 
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }



    //se placer à la ligne passé en param, en utilisant à chaque fois la taille de sudoku présente au début de chaque ligne pour aller plus vite 

    //lecture de la taille du sudoku, à refaire 
    int sudoku_length = 3; // premier char 

    // Allouer de la mémoire pour le tableau sudoku_array
    //on peut pas faire ça, il faut d'abord lire le fichier pour connaître la longueur de l'array
    new_sudoku->sudoku_array = (char**)malloc( (int)(pow((double)sudoku_length,4.0)) * sizeof(char*));
    if (new_sudoku->sudoku_array == NULL) {
        // Gestion de l'erreur de mémoire
        free(new_sudoku);
        return NULL;
    }



    if (ferror(file)) {
        // Erreur de lecture
        perror("Erreur lors de la lecture de la ligne");
        free(line);
        fclose(file);
        return NULL;
    }

    fclose(file);
    return new_sudoku;

}
//indique le nombre de violation de règle pour la grille 
void grid_cost(sudoku* sudoku_ptr, int line, int column);
//génère une solution aléatoire pour le sudoku
void new_solution(sudoku* sudoku_ptr);
void free_sudoku(sudoku* sudoku_ptr) {
    if (sudoku_ptr == NULL) {
        return;
    }

    int squared_length = sudoku_ptr->sudoku_length*sudoku_ptr->sudoku_length;

    // Libérer la mémoire pour le tableau sudoku_blocks
    for (int i = 0; i < squared_length; i++) {
        free(sudoku_ptr->sudoku_blocks[i]);
    }
    free(sudoku_ptr->sudoku_blocks);

    // Libérer la mémoire pour le tableau sudoku_array
    for (int i = 0; i < squared_length; i++) {
        free(sudoku_ptr->sudoku_array[i]);
    }
    free(sudoku_ptr->sudoku_array);

    // Libérer la mémoire de la structure sudoku elle-même
    free(sudoku_ptr);
}


