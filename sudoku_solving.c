#include "sudoku.h"
#include "stdlib.h"
//w1,w2,w3... un ensemble de solution 
//fonction economique c(w) 
//fonction de voisinage V : OMEGA donne 2 puissance OMEGA 

//à chaque itération une solution omega prime est choisit arbitrairement parmi toutes les solutions possibles 

//graphe de sudoku > les sommets sont les casses de la grille, deux sommets osnt liés s'ils sont sur la même ligne, colonne, sous carré 


void solve(sudoku* sudoku_ptr){
    //INITIALISATION 
    double delta = 0.1;
    double ep = 1620/2;
    double Temperature = ep;
    int i,j;
    unsigned int c = 0;
    unsigned int c1 = 0;
    unsigned int c2 = 0;
    unsigned int c_prime = 0;
    solution temporaire;

    //choisir une solution arbitrairement 
    //omega = choisirSolution();
    solution omega = choisirSolution(sudoku_ptr);

    while(Temperature >= 0.00273852){
        for(int k = 1; k <= 81; k++){
            //choisir i et j dans {1,9} (vérifier que c'est pas une case déjà prise)
            i = rand_r()%9+1;
            j = rand_r()%9+1;

            temporaire = omegaij;
            c1 = cost(omegaij);

            do{
                omegaij = solutionaleatoirepourlacase
            }
            while (omegaij == temporaire)

            c2 = cost(omegaij)
            c_prime = c-c1+c2

            //choisir u dans   [0,1]
            u = rand_r truc 

            if(u <= e*((c_prime-c)/Temperature)){
                c = c_prime;//acceptation
            } else {
                omegaij = temporaire;//rejet
            }
            if(c == 0){
                
                //écrire omega dans la case 
            }
        }
        Temperature = ( Temperature / ( 1 + ( log(1 + delta) / exp( p + 1 )) * Temperature ));
        
    }
}