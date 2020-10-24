//
// Created by antho on 10/20/2020.
//

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <ctime>      // for time(NULL)
#include "geesespotter_lib.h"
#include "geesespotter.h"

//my helper funcs
int DN(char *board, std::size_t xdim, int i) {
    int pos = i - xdim;
    if (board[pos] == 9) {
        return 1;
    } else {
        return 0;
    }
}

int NE(char *board, std::size_t xdim, int i) {
    int pos = i - xdim + 1;
    if (board[pos] == 9) {
        return 1;
    } else {
        return 0;
    }
}

int DE(char *board, std::size_t xdim, int i) {
    int pos = i + 1;
    if (board[pos] == 9) {
        return 1;
    } else {
        return 0;
    }
}

int SE(char *board, std::size_t xdim, int i) {
    int pos = i + xdim + 1;
    if (board[pos] == 9) {
        return 1;
    } else {
        return 0;
    }
}

int DS(char *board, std::size_t xdim, int i) {
    int pos = i + xdim;
    if (board[pos] == 0) {
        return 1;
    } else {
        return 0;
    }
}

int SW(char *board, std::size_t xdim, int i) {
    int pos = i + xdim - 1;
    if (board[pos] == 9) {
        return 1;
    } else {
        return 0;
    }
}

int DW(char *board, std::size_t xdim, int i) {
    int pos = i - 1;
    if (board[pos] == 9) {
        return 1;
    } else {
        return 0;
    }
}

int NW(char *board, std::size_t xdim, int i) {
    int pos = i - xdim - 1;
    if (board[pos] == 9) {
        return 1;
    } else {
        return 0;
    }
}

char *createBoard(std::size_t xdim, std::size_t ydim) {

    char *board{new char[xdim * ydim]};
    for (int i{0}; i < (xdim*ydim); ++i) {
        board[i] = 0x00;
    }

    return board;
}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim) {

    /*
     * compute all edge cases?
     * compute all interior cases?
     */

    /*
     * 01234
     * 56789
     */
    int row{};
    int col{};
    int neighbours{};
    char *newBoard{new char[xdim * ydim]};
    for (int i{0}; i <(xdim*ydim); ++i) {
        newBoard[i] = 0x00;
    }

    for (int i{0}; i < (xdim * ydim); ++i) {
//
//         *  NW DN NE
//         *  DW CR DE
//         *  SW DS SE
//
        // can you add? ^ find the value for each. if there is a neighobur that is a geese, add 1 to the count. Go through the neighoburs, and check to ensure that hey're in bound.

        row = i / xdim; // how many times have we travelled the full board across?
        col = i % xdim; // how far are we on this traversal?

        if (board[i] == 9) {
            // do nothing
            newBoard[i] = 9;
        } else {
            if (row == 0) {
                // not allowed to have north neighbours.
                if (col == 0) {
                    // not allowed to have west neighbours?
                    // DE SE DS
                    newBoard[i] = DE(board, xdim, i) + SE(board, xdim, i) + DS(board, xdim, i);
                } else if (col == (xdim - 1)) {
                    // not allowed to have east neighbours
                    // DW SW DS
                    newBoard[i] = DW(board, xdim, i) + SW(board, xdim, i) + DS(board, xdim, i);
                } else {
                    // allowed to have neighbours s/w
                    // DW SW DS SE DE
                    newBoard[i] = DW(board, xdim, i) + SW(board, xdim, i) + DS(board, xdim, i) + SE(board, xdim, i) +
                                  DE(board, xdim, i);
                }
            } else if (row == (ydim - 1)) {
                //not allowed to have south neighbours
                if (col == 0) {
                    // not allowed to have west neighbours?
                    // DN NE DE
                    newBoard[i] = DN(board, xdim, i) + NE(board, xdim, i) + DE(board, xdim, i);
                } else if (col == (xdim - 1)) {
                    // not allowed to have east neighbours
                    // DW NW DN
                    newBoard[i] = DW(board, xdim, i) + NW(board, xdim, i) + DN(board, xdim, i);
                } else {
                    // allowed to have neighbours s/w
                    // DW NW DN NE DE
                    newBoard[i] = DW(board, xdim, i) + NW(board, xdim, i) + DN(board, xdim, i) + NE(board, xdim, i) +
                                  NE(board, xdim, i) + DE(board, xdim, i);
                }
            } else {
//            no restrictions vertically
                if (col == 0) {
                    // not allowed to have west neighbours?
                    // DN NE DE SE DS
                    newBoard[i] = DN(board, xdim, i) + NE(board, xdim, i) + DE(board, xdim, i) + SE(board, xdim, i) +
                                  DS(board, xdim, i);
                } else if (col == (xdim - 1)) {
                    // not allowed to have east neighbours
                    // DN NW DW SW DS
                    newBoard[i] = DN(board, xdim, i) + NW(board, xdim, i) + DW(board, xdim, i) + SW(board, xdim, i) +
                                  DS(board, xdim, i);
                } else {
                    // allowed to have neighbours in every direction.
                    // DN NE DE SE DS SW DW NW
                    newBoard[i] = DN(board, xdim, i) + NE(board, xdim, i) + DE(board, xdim, i) + SE(board, xdim, i) +
                                  DS(board, xdim, i) + SW(board, xdim, i) + DW(board, xdim, i) + NW(board, xdim, i);
                }
            }
        }


    }
    for (int i{0}; i < (xdim * ydim); ++i) {
        board[i] = newBoard[i];
    }
}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim) {
    for (int i{0}; i < (xdim * ydim); ++i) {
//        board[i] += 0x20;
    }

}

void cleanBoard(char *board) {
};

void printBoard(char *board, std::size_t xdim, std::size_t ydim) {
    /* output board itself ?
     * can be *, num, or Marked. Precedence Mraked, Hidden, Num.
    */

    for (int print_index{0}; print_index < (xdim * ydim); ++print_index) {
        if ((print_index % 5) == 0) {
            std::cout << std::endl;
        }
        if (board[print_index] & markedBit()) { // or == markedBit(); - in c++ any non-zero = true, 0 = false.
            //using pointer as an array is perfectly valid?
            std::cout << 'M' << " ";
        } else if (board[print_index] & hiddenBit()) {
            std::cout << '*' << " ";
        } else {
            std::cout << (int) board[print_index] << " "; //typecasts the char to int
        }

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