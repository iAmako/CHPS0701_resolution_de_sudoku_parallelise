#include "sudoku.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <stdlib.h>

#define TAILLE_SUDOKU 3

// charge un sudoku en mémoire, un sudoku est représenté par une ligne dans un fichier "."
sudoku *load_sudoku(FILE *filename, int line_number)
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
    int char_nb = (int)pow((double)(sudoku_length), 4.0);

    new_sudoku->sudoku_length = sudoku_length;

    // Allouer de la mémoire pour le tableau sudoku_array
    // on peut pas faire ça, il faut d'abord lire le fichier pour connaître la longueur de l'array
    new_sudoku->sudoku_array = (char **)malloc((int)(pow((double)sudoku_length, 4.0)) * sizeof(char *));
    if (new_sudoku->sudoku_array == NULL)
    {
        // Gestion de l'erreur de mémoire
        free(new_sudoku);
        return NULL;
    }

    // Allouer de la mémoire pour le tableau sudoku_blocks
    new_sudoku->sudoku_blocks = (char **)malloc((int)(pow((double)sudoku_length, 4.0)) * sizeof(char *));
    if (new_sudoku->sudoku_blocks == NULL)
    {
        // Gestion de l'erreur de mémoire
        free(new_sudoku);
        return NULL;
    }

    char c = NULL;

    for (int i = 0; i < line_col_length; i++)
    {
        for (int j = 0; j < line_col_length; j++)
        {
            while ((c = fgetc(file)) != EOF)
            {
                // Process the character (e.g., print it)
                new_sudoku->sudoku_array[i][j] = c;
            }
            //TODO REMPLIR LES BLOCS 
            // new_sudoku->sudoku_blocks[][];
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
    int cur_value = sudoku_ptr->sudoku_array[i][j];
    int line_col_len = sudoku_ptr->sudoku_length * sudoku_ptr->sudoku_length;
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
        //bloc
        if(j != k){
            if(cur_value == sudoku_ptr->sudoku_array[i][k]){
                ++cost;
            }
        }
    }
}

// indique le nombre de violation de règle pour la grille
unsigned int grid_cost(sudoku *sudoku_ptr){
    unsigned int cost = 0;
    int cur_line_value = 0;
    int cur_col_value = 0;
    int cur_block_value = 0;

    int line_col_len = sudoku_ptr->sudoku_length*sudoku_ptr->sudoku_length;
    for (int i = 0; i < line_col_len; i++)
    {        
        for (int j = 0; j < line_col_len; j++)
        {
            cur_line_value = sudoku_ptr->sudoku_array[i][j];
            cur_col_value = sudoku_ptr->sudoku_array[i][j];
            cur_block_value = sudoku_ptr->sudoku_blocks[i][j];
            for(int k = 0; k < line_col_len; k++){
                //line
                if(j != k){
                    if(cur_line_value == sudoku_ptr->sudoku_array[i][k]){
                        ++cost;
                    }
                }
                //column
                if(i != k){
                    if(cur_col_value == sudoku_ptr->sudoku_array[k][j]){
                        ++cost;
                    }
                }
                //bloc
                if(j != k){
                    if(cur_block_value == sudoku_ptr->sudoku_array[i][k]){
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

    sudoku *new_sudoku = (sudoku *)malloc(sizeof(sudoku));
    if (new_sudoku == NULL)
    {
        // Gestion de l'erreur de mémoire
        return NULL;
    }

    new_sudoku->sudoku_length = sudoku_ptr->sudoku_length;

    // Allouer de la mémoire pour le tableau sudoku_array
    // on peut pas faire ça, il faut d'abord lire le fichier pour connaître la longueur de l'array
    new_sudoku->sudoku_array = (char **)malloc((int)(pow((double)sudoku_ptr->sudoku_length, 4.0)) * sizeof(char *));
    if (new_sudoku->sudoku_array == NULL)
    {
        // Gestion de l'erreur de mémoire
        free(new_sudoku);
        return NULL;
    }

    // Allouer de la mémoire pour le tableau sudoku_blocks
    new_sudoku->sudoku_blocks = (char **)malloc((int)(pow((double)sudoku_ptr->sudoku_length, 4.0)) * sizeof(char *));
    if (new_sudoku->sudoku_blocks == NULL)
    {
        // Gestion de l'erreur de mémoire
        free(new_sudoku);
        return NULL;
    }


    int line_col_length = (sudoku_ptr->sudoku_length*sudoku_ptr->sudoku_length);

    for (int i = 0; i < sudoku_ptr->sudoku_length; i++)
    {
        for (int j = 0; j < sudoku_ptr->sudoku_length; j++)
        {
            if(sudoku_ptr->sudoku_array[i][j] == 0){
                new_sudoku->sudoku_array[i][j] = rand_r()%9+1;
            } else {
                new_sudoku->sudoku_array[i][j] = sudoku_ptr->sudoku_array;
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
