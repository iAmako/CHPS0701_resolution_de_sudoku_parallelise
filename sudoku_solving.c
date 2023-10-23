#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

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
    char temporaire;
    double cons = log(1+delta);
    unsigned int seed = 0;
    char tmp_solution = '0';
    double u = 0;
    int nb_of_cases = pow(sudoku_ptr->sudoku_length,4);
    unsigned int nbEssais = 0;
    
    seed = omp_get_thread_num() + time(NULL);

    printf("grille : \n");
    print_sudoku(sudoku_ptr);


    //choisir une solution arbitrairement 
    //omega = choisirSolution();
    sudoku* omega = new_solution(sudoku_ptr);

    printf("premiere solution aléatoire : \n");
    print_sudoku(omega);

    //calcul du cout de la grille
    c = grid_cost(omega);

    printf("%u violations de règles\n",c);


    while(c != 0 || Temperature >= 0.00273852){

        for(int k = 1; k <= nb_of_cases; k++){

            //choisir i et j dans {1,9} (vérifier que c'est pas une case déjà prise)
            do{
                i = rand_r(&seed)%9;
                j = rand_r(&seed)%9;
            } while (sudoku_ptr->sudoku_array[i][j] != '0'); 


            temporaire = omega->sudoku_array[i][j];

            c1 = case_cost(omega,i,j);

            do{
                tmp_solution = ((rand_r(&seed)%9+1) + '0');//nouvelle solution aléatoire entre 1 et 9 
                omega->sudoku_array[i][j] = tmp_solution;
                omega->sudoku_blocks[block_nb(i,j,omega->sudoku_length)][pos_in_block(i,j,omega->sudoku_length)] = tmp_solution; //ajouter la division euclidienne 
            }
            while (omega->sudoku_array[i][j] == temporaire);



            c2 = case_cost(omega,i,j);

            //printf("%d %d case cost : %u",i,j,c2);

            c_prime = c-c1+c2;



            //choisir u dans   [0,1]
            u = ((double)rand_r(&seed))/RAND_MAX;
            
            //printf("u : %lf\n",u);

            if(omega->sudoku_array[i][j] != omega->sudoku_blocks[block_nb(i,j,omega->sudoku_length)][pos_in_block(i,j,omega->sudoku_length)]){
                printf("probleme calcul bloc !!!\n");
            } 

            if(u > exp(-(((double)(c_prime-c))/Temperature))){
                c = c_prime;//acceptation
                //printf("New total cost : %u\n",c);
                //printf("grille de base : \n");
                //print_sudoku(sudoku_ptr);
                //printf("new solution : \n");
                //print_sudoku(omega);
            } else {
                //printf("New total cost refusé : %u\n",c);
                omega->sudoku_array[i][j] = temporaire;//rejet
                omega->sudoku_blocks[block_nb(i,j,omega->sudoku_length)][pos_in_block(i,j,omega->sudoku_length)] = temporaire;
            }
            if(c == 0){
                printf("Nombre d'essais : %u\n",nbEssais);
                return omega;
            } 
        }
        //printf("i : %d, j : %d, temporaire : %c\n",i,j,omega->sudoku_array[i][j]);
        ++nbEssais;
        Temperature = ( Temperature / ( 1 + ( log(1 + delta) / (ep + 1)) * Temperature ));
        printf("Coût total : %u\nTemperature : %lf\n",c,Temperature);
        print_sudoku(omega);

        
    }

    return omega;
}