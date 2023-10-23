#include "sudoku.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define TAILLE_SUDOKU 3

//donne le numéro de bloc (entre 0 et 8 ) corresopndant aux ligne/col (entre 0 et 8 ) passé en paramètres dépendant la taille du sudoku
int block_nb(int row, int col, int sudoku_length){
    return row / sudoku_length * sudoku_length + col / sudoku_length;
}
//donne la position (entre 0 et 8) d'une case dans un bloc de la grille 
int pos_in_block(int row, int col, int sudoku_length){
    return row % sudoku_length * sudoku_length + col % sudoku_length;
}

//donne les coordonnées dans le tableau de blocs correspondant aux coords du tableau de lignes/colonnes 
void block_coords(int row, int col, int sudoku_length, int* coords){
    coords[0] = row / sudoku_length * sudoku_length + col / sudoku_length;//bloc_pos 
    coords[1] = row % sudoku_length * sudoku_length + col % sudoku_length;//pos_in_bloc //EN FAIT CA MARCHE PEUT ETRE // TODO CEST PAS BON  IL Y A DU MODULO QUELQUE PART  //  CEST COMME REDUIRE EN UNE SEULE GRILLE 
}

void print_sudoku(sudoku* su){
    int row_col_length = su->sudoku_length*su->sudoku_length;
    for (int i = 0; i < row_col_length; i++)
    {
        for (int j = 0; j < row_col_length; j++)
            {
                printf("%c ",su->sudoku_array[i][j]);
                if(!((j+1)%su->sudoku_length)){
                    printf(" ");
                }
            }
        printf("\n");
        if(!((i+1)%su->sudoku_length)){
            printf("\n");
        }
    }
}

//Alloue la mémoire pour un sudoku non-initialisé passé en paramètre
int malloc_sudoku(sudoku* new_sudoku, int line_col_length){
        // Allouer de la mémoire pour le tableau sudoku_array
    // il faut d'abord lire le fichier pour connaître la longueur de l'array
    new_sudoku->sudoku_array = (char **)malloc((int)(line_col_length) * sizeof(char *));
    if (new_sudoku->sudoku_array == NULL)
    {
        // Gestion de l'erreur de mémoire
        free(new_sudoku);
        return 1;
    }
    for(int i = 0; i<line_col_length;i++){
        new_sudoku->sudoku_array[i] = (char *)malloc((int)(line_col_length) * sizeof(char));
    }

    // Allouer de la mémoire pour le tableau sudoku_blocks
    new_sudoku->sudoku_blocks = (char **)malloc((int)(line_col_length) * sizeof(char *));
    if (new_sudoku->sudoku_blocks == NULL)
    {
        // Gestion de l'erreur de mémoire
        free(new_sudoku);
        return 1;
    }
    for(int i = 0; i<line_col_length;i++){
        new_sudoku->sudoku_blocks[i] = (char *)malloc((int)(line_col_length) * sizeof(char));
    }
    return 0;
}

// charge un sudoku en mémoire, un sudoku est représenté par une ligne dans un fichier "."
sudoku *load_sudoku(char* filename, int line_number)
{
    sudoku *new_sudoku = (sudoku *)malloc(sizeof(sudoku));
    if (new_sudoku == NULL)
    {
        // Gestion de l'erreur de mémoire
        return NULL;
    }

    // Ouverture du fichier
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }


    // TODO : CHANGER POUR ÊTRE UTILISABLE AVEC N'IMPORTE QUEL FICHIER
    // CHANGER POUR ÊTRE UTILISABLE AVEC LES SUDOKU 4*4,5*5...
    // se placer à la ligne passé en param, en utilisant à chaque fois la taille de sudoku présente au début de chaque ligne pour aller plus vite
    // lecture de la taille du sudoku

    if (ferror(file))
    {
        // Erreur de lecture
        perror("Erreur lors de la lecture de la ligne");    
        fclose(file);
        return NULL;
    }



    // lecture de la taille du sudoku, à refaire
    int sudoku_length = 3; // premier char
    int line_col_length = sudoku_length * sudoku_length;
    //int char_nb = (int)pow((double)(sudoku_length), 3.0);

    if(malloc_sudoku(new_sudoku,line_col_length)){
        printf("Erreur à l'allocation mémoire\n");
        return NULL;
    }

    new_sudoku->sudoku_length = sudoku_length;

    char c = '0';

    for (int i = 0; i < line_col_length; i++)
    {
        for (int j = 0; j < line_col_length; j++)
        {
            c = fgetc(file);   
            // Place the character in Array&Block
            new_sudoku->sudoku_array[i][j] = c;
            new_sudoku->sudoku_blocks[block_nb(i,j,sudoku_length)][pos_in_block(i,j,sudoku_length)];
        }
    }


    // new_sudoku->sudoku_blocks[][];

    if (ferror(file))
    {
        // Erreur de lecture
        perror("Erreur lors de la lecture de la ligne");
        fclose(file);
        return NULL;
    }

    fclose(file);
    return new_sudoku;
}

//indique le nombre de violation de règle pour la case spécifiée en paramètres
unsigned int case_cost(sudoku *sudoku_ptr, int i, int j){
    unsigned int cost = 0;
    int line_col_len = sudoku_ptr->sudoku_length * sudoku_ptr->sudoku_length;

    char cur_value = sudoku_ptr->sudoku_array[i][j];
    int cur_block = block_nb(i,j,sudoku_ptr->sudoku_length);
    int cur_pos_in_block = pos_in_block(i,j,sudoku_ptr->sudoku_length);

    for(int k = 0; k < line_col_len; k++){
        //line
        //printf("%c != %c?\n",cur_value,sudoku_ptr->sudoku_array[i][k]);
        if(j != k){
            if(cur_value == sudoku_ptr->sudoku_array[i][k]){
                ++cost;
                //printf("yes, cout : %u\n",cost);
            }
        }
        //column
        //printf("%c != %c?\n",cur_value,sudoku_ptr->sudoku_array[k][j]);
        if(i != k){
            if(cur_value == sudoku_ptr->sudoku_array[k][j]){
                ++cost;
                //printf("yes, cout : %u\n",cost);

            }
        }
        //bloc // peut etre mieux de le faire dans une autre boucle 
        if(cur_pos_in_block != k){
            //printf("%c != %c?\n",cur_value, sudoku_ptr->sudoku_array[cur_block][k]);
            if(cur_value == sudoku_ptr->sudoku_array[cur_block][k]){
                ++cost;
                //printf("yes, cout : %u\n",cost);
            }
        }
    }
    return cost;
}

// indique le nombre de violation de règle pour la grille
unsigned int grid_cost(sudoku *sudoku_ptr){
    unsigned int cost = 0;
    char cur_value = 0;
    int cur_block = 0;
    int cur_pos_in_block = 0;

    int line_col_len = sudoku_ptr->sudoku_length*sudoku_ptr->sudoku_length;
    for (int i = 0; i < line_col_len; i++)
    {        
        for (int j = 0; j < line_col_len; j++)
        {
            cur_value = sudoku_ptr->sudoku_array[i][j];
            cur_block = block_nb(i,j,sudoku_ptr->sudoku_length);
            cur_pos_in_block = pos_in_block(i,j,sudoku_ptr->sudoku_length);

            for(int k = 0; k < line_col_len; k++){
                //line
                if(j != k){
                    if(cur_value == sudoku_ptr->sudoku_array[i][k]){
                        ++cost;
                    }
                }
                //column
                if(i != k){
                    if(cur_value == sudoku_ptr->sudoku_array[k][j]){
                        ++cost;
                    }
                }
                //bloc // peut etre mieux de le faire dans une autre boucle 
                if(cur_pos_in_block != k){
                    if(cur_value == sudoku_ptr->sudoku_array[cur_block][k]){
                        ++cost;
                    }
                }
            }
        }
    }
    return cost;
}
// génère une solution aléatoire pour le sudoku
sudoku* new_solution(sudoku *sudoku_ptr){

    unsigned int seed = (unsigned int)time(NULL)+omp_get_thread_num();

    sudoku *new_sudoku = (sudoku *)malloc(sizeof(sudoku));
    if (new_sudoku == NULL)
    {
        // Gestion de l'erreur de mémoire
        return NULL;
    }

    int line_col_length = (sudoku_ptr->sudoku_length*sudoku_ptr->sudoku_length);


    if(malloc_sudoku(new_sudoku,line_col_length)){
        printf("Erreur à l'allocation mémoire\n");
        return NULL;
    }

    new_sudoku->sudoku_length = sudoku_ptr->sudoku_length;

    for (int i = 0; i < line_col_length; i++)
    {
        for (int j = 0; j < line_col_length; j++)
        {
            if(sudoku_ptr->sudoku_array[i][j] == '0'){
                new_sudoku->sudoku_array[i][j] = ((rand_r(&seed)%9+1) + '0');
                new_sudoku->sudoku_blocks[block_nb(i,j,new_sudoku->sudoku_length)][pos_in_block(i,j,new_sudoku->sudoku_length)] = new_sudoku->sudoku_array[i][j];
            } else {

                new_sudoku->sudoku_array[i][j] = sudoku_ptr->sudoku_array[i][j];
                new_sudoku->sudoku_blocks[block_nb(i,j,new_sudoku->sudoku_length)][pos_in_block(i,j,new_sudoku->sudoku_length)] = new_sudoku->sudoku_array[i][j];
            }
        }
    }

    return new_sudoku;
}



void free_sudoku(sudoku *sudoku_ptr)
{
    if (sudoku_ptr == NULL)
    {
        return;
    }

    int squared_length = sudoku_ptr->sudoku_length * sudoku_ptr->sudoku_length;

    // Libérer la mémoire pour le tableau sudoku_blocks
    for (int i = 0; i < squared_length; i++)
    {
        free(sudoku_ptr->sudoku_blocks[i]);
    }
    free(sudoku_ptr->sudoku_blocks);

    // Libérer la mémoire pour le tableau sudoku_array
    for (int i = 0; i < squared_length; i++)
    {
        free(sudoku_ptr->sudoku_array[i]);
    }
    free(sudoku_ptr->sudoku_array);

    // Libérer la mémoire de la structure sudoku elle-même
    free(sudoku_ptr);
}
