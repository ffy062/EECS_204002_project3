#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/


// ver0-0 random algorithm
// ver0-1 random algorithm with explode detection and corner first strategy



bool check_adj(Board board, int color, int i, int j);

void algorithm_A(Board board, Player player, int index[]){

    //srand(time(NULL));
    int row, col;
    int color = player.get_color();

    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 6; ++j) {
            if(board.get_orbs_num(i, j) + 1 == board.get_capacity(i, j)) {
                if(check_adj(board, color, i, j)) {
                    index[0] = i;
                    index[1] = j;
                    return;
                }
            }
        }
    }
    
    if(board.get_cell_color(0, 0) == color || board.get_cell_color(0, 0) == 'w') {
        index[0] = 0;
        index[1] = 0;
    }
    else if(board.get_cell_color(0, 5) == color || board.get_cell_color(0, 5) == 'w') {
        index[0] = 0;
        index[1] = 5;
    }
    else if(board.get_cell_color(4, 0) == color || board.get_cell_color(4, 0) == 'w') {
        index[0] = 4;
        index[1] = 0;
    }
    else if(board.get_cell_color(4, 5) == color || board.get_cell_color(4, 5) == 'w'){
        index[0] = 4;
        index[1] = 5;
    }
    else {
        while(1){
            row = rand() % 5;
            col = rand() % 6;
            if(board.get_cell_color(row, col) == color || board.get_cell_color(row, col) == 'w') break;
        }
        index[0] = row;
        index[1] = col;
    }
}


bool check_adj(Board board, int color, int i, int j) {
    bool al_explode = false;

    if(i - 1 >= 0) {
        if(board.get_cell_color(i-1, j) != color && board.get_orbs_num(i-1, j) + 1 == board.get_capacity(i-1, j)) {
            al_explode = true;
        }
    }
    if(i + 1 < 5) {
         if(board.get_cell_color(i+1, j) != color && board.get_orbs_num(i+1, j) + 1 == board.get_capacity(i+1, j)) {
            al_explode = true;
        }
    }
    if(j - 1 >= 0) {
         if(board.get_cell_color(i, j-1) != color && board.get_orbs_num(i, j-1) + 1 == board.get_capacity(i, j-1)) {
            al_explode = true;
        }
    }
    if(j + 1 < 6) {
         if(board.get_cell_color(i, j+1) != color && board.get_orbs_num(i, j+1) + 1 == board.get_capacity(i, j+1)) {
            al_explode = true;
        }
    }

    return al_explode;
}