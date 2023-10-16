#ifndef SUDOKU_SOLVING_H
#define SUDOKU_SOLVING_H
#include "sudoku.h"
//w1,w2,w3... un ensemble de solution 
//fonction economique c(w) 
//fonction de voisinage V : OMEGA donne 2 puissance OMEGA 

//à chaque itération une solution omega prime est choisit arbitrairement parmi toutes les solutions possibles 

//graphe de sudoku > les sommets sont les casses de la grille, deux sommets osnt liés s'ils sont sur la même ligne, colonne, sous carré 


void solve(sudoku* sudoku_ptr);
#endif SUDOKU_SOLVING_H


