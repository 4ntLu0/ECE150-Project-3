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

int TL(char *board, std::size_t xdim) {
    if (board[0] == 9) {
        return 9;
    }
    int nums{0};
    if (board[1] == 9) {
        nums += 1;
    }
    if (board[xdim] == 9) {
        nums += 1;
    }
    if (board[xdim + 1] == 9) {
        nums += 1;
    }
    std::cout << "TopLeft Neighoburs: " << nums << std::endl;
    return nums;
}

int TR(char *board, std::size_t xdim) {
    if (board[xdim - 1] == 9) {
        return 9;
    }
    int nums{0};
    if (board[xdim - 2] == 9) {
        nums += 1;
    }
    if (board[2 * xdim - 1] == 9) { //xdim-1 is TR row. add XDIM to get one below.
        nums += 1;
    }
    if (board[2 * xdim - 2] == 9) { // see above, but now we move one left.
        nums += 1;
    }
    std::cout << "TopRight Neighbours: " << nums << std::endl;
    return nums;
}

int BL(char *board, std::size_t xdim, std::size_t ydim) {
    int pos = (xdim * ydim - xdim);
    if (board[pos] == 9) {
        return 9;
    }
    int nums{};
    if (board[pos - xdim] == 9) { // directly above pos
        nums += 1;
    }
    if (board[pos - xdim + 1] == 9) { //to the right and above
        nums += 1;
    }
    if (board[pos + 1] == 9) { // to the right
        nums += 1;
    }
    std::cout << "BottomLeft Neighbours: " << nums << std::endl;
    return nums;
}

int BR(char *board, std::size_t xdim, std::size_t ydim) {
    int pos = (xdim * ydim - 1);
    if (board[pos] == 9) {
        return 9;
    }
    int nums{};
    if (board[pos - xdim] == 9) { //right above
        nums += 1;
    }
    if (board[pos - xdim - 1] == 9) { //diagonal above to left
        nums += 1;
    }
    if (board[pos - 1] == 9) { // directly to left
        nums += 1;
    }
    std::cout << "BottomRight Neigbours: " << nums << std::endl;
    return nums;
}


char *createBoard(std::size_t xdim, std::size_t ydim) {

    char *board{new char[xdim * ydim]};
    for (int i{0}; i < (xdim * ydim); ++i) {
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
     *
     * 0123
     * 4567
     */
    int row{};
    int col{};
    int neighbours{};

    char *newBoard = new char[xdim * ydim];
    for (int i{0}; i < (xdim * ydim); ++i) {
        newBoard[i] = 0x00;
    }

    // can try to solve corner cases, then do inner suite.

    //solve (0,0)
    board[0] = TL(board, xdim);
    //solve (xdim, 0)
    board[xdim - 1] = TR(board, xdim);
    //solve (0, ydim) <- ydim * xdim - xdim.
    board[xdim * ydim - xdim] = BL(board, xdim, ydim);
    //solve (xdim, ydim) <- xdim * ydim - 1
    board[xdim * ydim - 1] = BR(board, xdim, ydim);


    int nums{};
    int pos{};
    // solve inner upper row
    for (pos = 1; pos < (xdim - 2); ++pos) {
        nums = 0;
        if (board[pos] == 9) {
            newBoard[pos] = 9;
        } else {
            if (board[pos - 1] == 9) { // to the left
                nums += 1;
            }
            if (board[pos + 1] == 9) { // to the right
                nums += 1;
            }
            if (board[pos + xdim] == 9) { // below
                nums += 1;
            }
            if (board[pos + xdim - 1] == 9) { //below to left
                nums += 1;
            }
            if (board[pos + xdim + 1] == 9) { //below to right
                nums += 1;
            }
            board[pos] = (char) nums;
        }
    }

    // solve lower row?
    for (pos = xdim * ydim - xdim + 1; pos < (xdim * ydim - 2); ++pos) {
        nums = 0;
        if (board[pos] == 9) {
            board[pos] = 9;
        } else {
            if (board[pos - 1] == 9) { // to the left
                nums += 1;
            }
            if (board[pos + 1] == 9) { // to the right
                nums += 1;
            }
            if (board[pos - xdim] == 9) { // directly above
                nums += 1;
            }
            if (board[pos - xdim - 1] == 9) { // above and to the left
                nums += 1;
            }
            if (board[pos - xdim + 1] == 9) { // above and to the right
                nums += 1;
            }
            board[pos] = (char) nums;
        }
    }

        delete[] newBoard;
        newBoard = nullptr;
    }


void hideBoard(char *board, std::size_t xdim, std::size_t ydim) {
    for (int i{0}; i < (xdim * ydim); ++i) {
//        board[i] += 0x20;
    }

}

void cleanBoard(char *board) {
    delete[] board;
    board = nullptr;
};

void printBoard(char *board, std::size_t xdim, std::size_t ydim) {
    /* output board itself ?
     * can be *, num, or Marked. Precedence Mraked, Hidden, Num.
    */

    for (int print_index{0}; print_index < (xdim * ydim); ++print_index) {
        if ((print_index % xdim) == 0) {
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