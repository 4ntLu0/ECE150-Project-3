//
// Created by antho on 10/20/2020.
//
#include <iostream>
#include "geesespotter_lib.h"

//my helper funcs
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
//    std::cout << "TopLeft Neighoburs: " << nums << std::endl;
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
//    std::cout << "TopRight Neighbours: " << nums << std::endl;
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
//    std::cout << "BottomLeft Neighbours: " << nums << std::endl;
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
//    std::cout << "BottomRight Neigbours: " << nums << std::endl;
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
     * 56789 - 10
     *
     * 01
     * 23
     * 45
     * 67 - 8
     *
     *
     * 0123
     * 4567
     *  0  1  2  3  4  5  6
     0 00 01 02 03 04 05 06
     1 07 08 09 10 11 12 13
     2 14 15 16 17 18 19 20
     3 21 22 23 24 25 26 27
     4 28 29 30 31 32 33 34
     */
    int row{};
    int col{};
    int neighbours{};

    // can try to solve corner cases, then do inner suite.

    //solve (0,0)
    board[0] = TL(board, xdim);
    //solve (xdim, 0)
    board[xdim - 1] = TR(board, xdim);
    //solve (0, ydim) <- ydim * xdim - xdim.
    board[xdim * ydim - xdim] = BL(board, xdim, ydim);
    //solve (xdim, ydim) <- xdim * ydim - 1
    board[xdim * ydim - 1] = BR(board, xdim, ydim);

//    std::cout << "done calculating edges" << std::endl;

    int nums{};
    int pos{};
    // solve inner upper row
    for (pos = 1; pos < (xdim - 1); ++pos) {
//        std::cout << "solving upper edge with pos: " << pos << "// ";
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
//    std::cout << std::endl;
//    std::cout << "solved upper row" << std::endl << "--------------------" << std::endl;

    // solve lower row?
    for (pos = xdim * ydim - xdim + 1; pos < (xdim * ydim - 1); ++pos) {
        nums = 0;
//        std::cout << "solving lower edge with pos: " << pos << "// ";
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
//    std::cout << std::endl;
//    std::cout << "solved bottom row" << std::endl << "--------------------" << std::endl;

    //solve left edge
    for (pos = xdim; pos < xdim * ydim - xdim - 1; pos += xdim) {
        nums = 0;
        // i think this works.
//        std::cout << "solving left edge with pos: " << pos << "// ";
        if (board[pos] == 9) {
            board[pos] = 9; // this should be removed later.
        } else {
            if (board[pos + 1] == 9) { // to the right
                nums += 1;
            }
            if (board[pos - xdim] == 9) { // directly above
                nums += 1;
            }
            if (board[pos - xdim + 1] == 9) { // above and to the right
                nums += 1;
            }
            if (board[pos + xdim] == 9) { //directly below
                nums += 1;
            }
            if (board[pos + xdim + 1] == 9) { // below and to the right
                nums += 1;
            }
            board[pos] = (char) nums;
        }
    }
//    std::cout << std::endl;
//    std::cout << "solved left edge" << std::endl << "--------------------" << std::endl;

    //solve right edge
    for (pos = (xdim - 1 + xdim); pos < xdim * ydim - 2; pos += xdim) {
        nums = 0;
//        std::cout << "solving right edge with pos: " << pos << "// ";
        if (board[pos] == 9) {
            board[pos] = 9;
        } else {
            if (board[pos - 1] == 9) { // to the left
                nums += 1;
            }
            if (board[pos - xdim] == 9) { // above
                nums += 1;
            }
            if (board[pos + xdim] == 9) { // below
                nums += 1;
            }
            if (board[pos - xdim - 1] == 9) { // diag to left and above
                nums += 1;
            }
            if (board[pos + xdim - 1] == 9) { // diag to left and below
                nums += 1;
            }
            board[pos] = (char) nums;
        }
    }
//    std::cout << std::endl;
//    std::cout << "solved right edge" << std::endl << "--------------------" << std::endl;

    int i{};
    int curpos{};
    for (pos = xdim + 1; pos < xdim * ydim - xdim - 1; pos += xdim) { // this will just iterate through all the rows.
        for (i = 0; i < (xdim - 2); i++) { //iterates horizontally
            curpos = pos + i;
            nums = 0;
//            std::cout << "solving general case with curpos: " << curpos << "//- ";
            if (board[curpos] == 9) {
                board[curpos] = 9;
            } else {
                if (board[curpos - 1] == 9) {
                    nums += 1;
                }
                if (board[curpos + 1] == 9) {
                    nums += 1;
                }
                if (board[curpos + xdim] == 9) {
                    nums += 1;
                }
                if (board[curpos - xdim] == 9) {
                    nums += 1;
                }
                if (board[curpos - xdim - 1] == 9) {
                    nums += 1;
                }
                if (board[curpos - xdim + 1] == 9) {
                    nums += 1;
                }
                if (board[curpos + xdim - 1] == 9) {
                    nums += 1;
                }
                if (board[curpos + xdim + 1] == 9) {
                    nums += 1;
                }
                board[curpos] = (char) nums;
            }
        }
//        std::cout << std::endl;
    }
}


void hideBoard(char *board, std::size_t xdim, std::size_t ydim) {
    for (int i{0}; i < (xdim * ydim); ++i) {
        board[i] += 0x20; // this will hide the board if enabled.
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
        if (((print_index % xdim) == 0) && (print_index != 0)) {
            std::cout << std::endl;
        }
        if (board[print_index] & markedBit()) { // or == markedBit(); - in c++ any non-zero = true, 0 = false.
            //using pointer as an array is perfectly valid?
            std::cout << 'M';
        } else if (board[print_index] & hiddenBit()) {
            std::cout << '*';
        } else {
            std::cout << (int) board[print_index]; //typecasts the char to int
        }

    }
    std::cout << std::endl;

}

int non_recursive_reveal(char *board, std::size_t xdim, std::size_t dyim, std::size_t xloc, std::size_t yloc) {
    int pos = xdim * (yloc) + xloc; // have to find the position in terms of the array
    if ((board[pos] & markedBit()) == markedBit()) {
        // this field is marked, and we won't change it.
        return 1;
    }
    board[pos] = board[pos] & valueMask(); // if the board isn't marked, then there can't be geese around because originally
    // there was a 0, so now it has to be like this.
    return 0;
}

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {
    /*
     * returns 1 if field is mark
     * returns 2 if field is already revealed
     * return 9 if field contains a goose
     * return 0 otherwise.
     */
    int pos = xdim * (yloc) + xloc; // have to find the position in terms of the array
    if ((board[pos] & markedBit()) == markedBit()) {
        return 1;
    } else if ((board[pos] & valueMask()) == board[pos]) {
        return 2;
    } else if ((board[pos] & valueMask()) == 9) {
        board[pos] = board[pos] & valueMask();
        return 9;
    }
    board[pos] = board[pos] & valueMask();
    if (board[pos] == 0) {
        //if you swap these to 'reveal' you will have true minesweeper.
        if ((xloc != 0)) {
            non_recursive_reveal(board, xdim, ydim, xloc - 1, yloc);
        }
        if ((xloc != (xdim - 1))) {
            non_recursive_reveal(board, xdim, ydim, xloc + 1, yloc);
        }
        if (yloc != 0) {
            non_recursive_reveal(board, xdim, ydim, xloc, yloc - 1);
        }
        if (yloc != (ydim - 1)) {
            non_recursive_reveal(board, xdim, ydim, xloc, yloc + 1);
        }
        if ((xloc != 0) && (yloc != 0)) {
            non_recursive_reveal(board, xdim, ydim, xloc - 1, yloc - 1);
        }
        if ((xloc != 0) && (yloc != (ydim - 1))) {
            non_recursive_reveal(board, xdim, ydim, xloc - 1, yloc + 1);
        }
        if ((xloc != (xdim - 1)) && (yloc != (ydim - 1))) {
            non_recursive_reveal(board, xdim, ydim, xloc + 1, yloc + 1);
        }
        if ((xloc != (xdim - 1)) && (yloc != 0)) {
            non_recursive_reveal(board, xdim, ydim, xloc + 1, yloc - 1);
        }
    }
    return 0;
}

int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {
    int pos = xdim * (yloc) + xloc; // have to find the position in terms of the array
    if ((board[pos] & 0x0f) == board[pos]) {
        return 2;
    }
    if ((board[pos] & markedBit()) == markedBit()) { // board is already marked, so we will unmark.
        board[pos] -= markedBit();
    } else {
        board[pos] += markedBit();
    }
    return 0;
}


bool isGameWon(char *board, std::size_t xdim, std::size_t ydim) {

    // if ((not_goose) && (not_revealed)) {false}
    // basically all fields that aren't geese have to be revealed.
    //only fields with geese remain.

    //board[i]&valueMask()!=board[i] will give True if they're not equal, false if they are.
    for (int i{}; i < (xdim * ydim); ++i) {
        if (((board[i] & valueMask()) != 9) && ((board[i] & valueMask()) != board[i])) {
            return false; //board[i] is not revealed (either marked or hidden).
        }
    }
    return true; // game is won if nothing else happens.
}