#include "sudoku.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define TAILLE_SUDOKU 3


charger_sudoku(FILE *file, int line_nb, char ***sudoku)
{
    
    fgetc();
    while (fgetc(file) != '\n'){

    } 
}

charger_fichier(char *filename, FILE *fptr)// juste faire un fopen dans le main maybe
{ 
    FILE *fptr = fopen(filename, "r");
}
