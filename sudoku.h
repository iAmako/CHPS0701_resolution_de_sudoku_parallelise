#ifndef SUDOKU_H
#define SUDOKU_H
//sudoku découpé en 3 matrices ou une matrice 3D, lignes & colonnes & cases (3x3)

//char[9][9][9] = un sudoku ? 

typedef struct solution_s{
    float cout;
    float temperature;
    char sudoku_origine[9][9];
    char sudoku_solution[9][9];
}solution;


charger_fichier(char* filename,FILE* ptr)
void charger_sudoku(FILE* file, char*** sudoku);
void construire_graph();
void deduire_temperature();
void deduire_cout();
#endif 