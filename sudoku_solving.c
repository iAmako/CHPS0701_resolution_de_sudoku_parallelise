#include <stdlib.h>
#include <omp.h>
#include <math.h>

#include "sudoku.h"
//w1,w2,w3... un ensemble de solution 
//fonction economique c(w) 
//fonction de voisinage V : OMEGA donne 2 puissance OMEGA 

//à chaque itération une solution omega prime est choisit arbitrairement parmi toutes les solutions possibles



sudoku* solve_sudoku(sudoku* sudoku_ptr){
    //INITIALISATION 
    double delta = 0.1;
    double ep = 1620/2;
    double Temperature = ep;
    int i,j;
    unsigned int c = 0;
    unsigned int c1 = 0;
    unsigned int c2 = 0;
    unsigned int c_prime = 0;
    sudoku* temporaire;
    double cons = log(1+delta);
    unsigned int seed = 0;
    int tmp_solution = 0;

    //choisir une solution arbitrairement 
    //omega = choisirSolution();
    sudoku* omega = new_solution(sudoku_ptr);

    while(Temperature >= 0.00273852){
        for(int k = 1; k <= 81; k++){

            seed = omp_get_thread_num();

            //choisir i et j dans {1,9} (vérifier que c'est pas une case déjà prise)
            seed = (unsigned int)time(NULL)+omp_get_thread_num();
            i = rand_r(&seed)%9+1;
            j = rand_r(&seed)%9+1;

            temporaire = omega->sudoku_array[i][j];
            c1 = case_cost(omega,i,j);

            do{
                tmp_solution = rand_r(&seed)%9+1;;//nouvelle solution aléatoire entre 1 et 9 
                omega->sudoku_array[i][j] = tmp_solution;
                omega->sudoku_blocks[block_nb(i,j,omega->sudoku_length)][pos_in_block(i,j,omega->sudoku_length)] = tmp_solution; //ajouter la division euclidienne 
            }
            while (omega->sudoku_array[i][j] == temporaire);

            c2 = case_cost(omega,i,j);
            c_prime = c-c1+c2;

            //choisir u dans   [0,1]
            double u = ((double)rand_r(&seed) / RAND_MAX) * 2;

            if(u <= e*((c_prime-c)/Temperature)){
                c = c_prime;//acceptation
            } else {
                omega->sudoku_array[i][j] = temporaire;//rejet
                omega->sudoku_blocks[block_nb(i,j,omega->sudoku_length)][pos_in_block(i,j,omega->sudoku_length)] = temporaire;
            }
            if(c == 0){
                
                //écrire omega dans la case 
            }
        }
        Temperature = ( Temperature / ( 1 + ( log(1 + delta) / exp( p + 1 )) * Temperature ));
        
    }

    return omega;
}