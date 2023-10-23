#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

#include "sudoku.h"
// w1,w2,w3... un ensemble de solution
// fonction economique c(w)
// fonction de voisinage V : OMEGA donne 2 puissance OMEGA

// à chaque itération une solution omega prime est choisit arbitrairement parmi toutes les solutions possibles

sudoku *solve_sudoku(sudoku *sudoku_ptr)
{
    // INITIALISATION
    double delta = 0.1;
    int nb_of_cases = pow(sudoku_ptr->sudoku_length, 4);
    double ep = (nb_of_cases * 10) / 2;
    int line_col_len = sudoku_ptr->sudoku_length * sudoku_ptr->sudoku_length;
    double Temperature = ep;
    int i, j;
    unsigned int c = 0;
    unsigned int c1 = 0;
    unsigned int c2 = 0;
    unsigned int c_prime = 0;
    char temporaire;
    double cons = log(1 + delta);
    unsigned int seed = 0;
    char tmp_solution = '0';
    double u = 0;
    unsigned int nbEssais = 0;
    srand(time(NULL));

    seed = omp_get_thread_num() + time(NULL);

    printf("grille : \n");
    print_sudoku(sudoku_ptr);

    // choisir une solution arbitrairement
    // omega = choisirSolution();
    sudoku *omega = new_solution(sudoku_ptr,&seed);

    printf("premiere solution aléatoire : \n");
    print_sudoku(omega);

    // calcul du cout de la grille
    c = grid_cost(omega);

    printf("%u violations de règles\n", c);

    while (c != 0)
    {
        ++nbEssais;
        double Temperature = ep;

        while (c != 0 && Temperature >= 0.00273852)
        {

            for (int k = 1; k <= nb_of_cases; k++)
            {

                // choisir i et j dans {1,9} (vérifier que c'est pas une case déjà prise)
                do
                {
                    i = rand_r(&seed) % line_col_len;
                    j = rand_r(&seed) % line_col_len;
                } while (sudoku_ptr->sudoku_array[i][j] != '0');

                temporaire = omega->sudoku_array[i][j];

                c1 = case_cost(omega, i, j);

                do
                {
                    tmp_solution = ((rand_r(&seed) % line_col_len + 1) + '0'); // nouvelle solution aléatoire entre 1 et 9

                } while (tmp_solution == temporaire);

                omega->sudoku_array[i][j] = tmp_solution;
                omega->sudoku_blocks[block_nb(i, j, omega->sudoku_length)][pos_in_block(i, j, omega->sudoku_length)] = tmp_solution;

                c2 = case_cost(omega, i, j);
                c_prime = c - c1 + c2;

                // choisir u dans   [0,1]
                // u = ((double)rand_r(&seed)) / RAND_MAX;
                u = (1.0*rand_r(&seed)) / RAND_MAX;

                printf("%lf | %lf | %lf\n",exp(-(((double)(c_prime - c)) / Temperature)),Temperature,u);

                if (u <= exp(-((((double)c_prime - (double)c)) / Temperature)))
                    
                {
                    c = c_prime; // acceptation
                    // printf("New total cost : %u\n",c);
                    // printf("grille de base : \n");
                    // print_sudoku(sudoku_ptr);
                    // printf("new solution : \n");
                    // print_sudoku(omega);
                }
                else
                {
                    // printf("New total cost refusé : %u\n",c);
                    omega->sudoku_array[i][j] = temporaire; // rejet
                    omega->sudoku_blocks[block_nb(i, j, omega->sudoku_length)][pos_in_block(i, j, omega->sudoku_length)] = temporaire;
                }
                
                //FIX RAPIDE A ENLEVER ÇA RALENTI DE FOU

            }
            Temperature = (Temperature / (1 + (log(1 + delta) / (ep + 1)) * Temperature));
            c = grid_cost(omega);

        }
        printf("Coût total : %u\nTemperature : %lf\nNombre d'essais : %d\n", c, Temperature, nbEssais);
        print_sudoku(omega);
        printf("Tableau des violations de containtes : \n");
        print_contraintes(omega);
        printf("\n\n\n");
    }
    return omega;
}