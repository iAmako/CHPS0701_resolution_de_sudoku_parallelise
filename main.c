#include <stdio.h>
#include "sudoku.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s file_path lline_nb\n", argv[0]);
        return 1;
    }

    char* arg1 = argv[1];
    int line_nb = (int)argv[2];
