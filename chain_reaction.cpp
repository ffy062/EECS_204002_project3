#include <iostream>
#include <fstream>
#include <time.h>
#include "../include/board.h"
#include "../include/player.h"
#include "../include/rules.h"
#include "../include/algorithm.h"
//#include "board.h"
//#include "player.h"
//#include "rules.h"
//#include "algorithm.h"


using namespace std;

//#define debug


// ver 0-0 upload the whole framework
// ver 0-1 modify chain_reaction.cpp and board.cpp to automatic play multiple times and calculate the result of each game.


int main(){

    Board board;
    Player red_player('r');
    Player blue_player('b');

    bool first_two_step = true;
    int round;
    int index[2];
    int exc_t, b_win, r_win;
    ofstream result;

    result.open("result.txt");
    cin >> exc_t;
    b_win = r_win = 0;
    srand(time(NULL));
    for(int i = 0; i < exc_t; ++i) {
        first_two_step = true;
        round = 1;
        board.all_reset();
        
        while(1){

            //////////// Red Player operations ////////////
            algorithm_A(board, red_player, index);
            board.place_orb(index[0], index[1], &red_player);

            if(rules_violation(red_player)) return 0;

            #ifdef debug
                board.print_current_board(index[0], index[1], round);
            #endif
            round++;

            if(board.win_the_game(red_player) && !first_two_step){
                cout << "Red Player won the game in round " << round << "!!!" << endl;
                r_win++;
                break;
            }

            //////////// Blue Player operations ////////////
            algorithm_E(board, blue_player, index);
            board.place_orb(index[0], index[1], &blue_player);

            if(rules_violation(blue_player)) return 0;

            #ifdef debug
                board.print_current_board(index[0], index[1], round);
            #endif
            round++;

            if(board.win_the_game(blue_player) && !first_two_step){
                cout << "Blue Player won the game in round " << round << "!!!" << endl;
                b_win++;
                break;
            }

            first_two_step = false;
        }
    }

    result << "Total rounds:\n" << "Red wins: " << r_win << endl << "Blue wins: " << b_win << endl;
    result.close();
    return 0;
} 


