#ifndef SUDOKU_SOLVING_H
#define SUDOKU_SOLVING_H
#include "sudoku.h"
//w1,w2,w3... un ensemble de solution 
//fonction economique c(w) 
//fonction de voisinage V : OMEGA donne 2 puissance OMEGA 

//à chaque itération une solution omega prime est choisit arbitrairement parmi toutes les solutions possibles 

//résoud un sudoku passé en paramètre, renvoie le sudoku résolu
sudoku* solve_sudoku(sudoku* sudoku_ptr);
#endif


