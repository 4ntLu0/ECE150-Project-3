//
// Created by antho on 10/20/2020.
//

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <ctime>      // for time(NULL)
#include "geesespotter_lib.h"
#include "geesespotter.h"

char *createBoard(std::size_t xdim, std::size_t ydim) {

    char *board{new char[xdim * ydim]};

    return board;
}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim) {

}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim) {

}

void cleanBoard(char *board) {

}

void printBoard(char *board, std::size_t xdim, std::size_t ydim) {
    /* output board itself ?
     * can be *, num, or Marked. Precedence Mraked, Hidden, Num.
    */

    int print_index{}; // just go through print index later in a loop KEKW.
    if (board[print_index] & markedBit()) { // or == markedBit(); - in c++ any non-zero = true, 0 = false.
        //using pointer as an array is perfectly valid?
        std::cout << 'M';
    } else if (board[print_index] & hiddenBit()) {
        std::cout << '*';
    } else {
        std::cout << (int) board[print_index]; //typecasts the char to int
    }

}

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {

    return 0;
}

int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {

    return 0;
}

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim) {

    return false;
}