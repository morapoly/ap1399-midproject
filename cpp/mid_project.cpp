#include "mid_project.h"

int run_puzzle(){
    char c1{}, c2{}, c3{}, c4{};
    int col{};
    std::cout << "Welcom to Number Puzzle\n";
    std::cout << "Do you want to solve or see?\n";
    while (!is_answer_char(c1)){
        std::cout << "(Enter y to solve a puzzle, or n to see how a puzzle is solved:)\n";
        std::cin >> c1;
    }
    std::cout << "The default puzzle is 8-Puzzle which is 3x3, Do you want to continue?\n";
    while (!is_answer_char(c2)){
        std::cout << "(Enter y to continue, or n to change the puzzle:)\n";
        std::cin >> c2;
    }
    if (!is_yes(c2)){
        std::cout << "Specify the puzzle columns or dimention.\n";
        while (col < 2 || col > 6 || !std::isdigit(c3)){
            std::cout << "(Enter an integer from 2 to 6 For example if you enter 4 the puzzle will be 4x4:)\n";
            std::cin >> c3;
            col = int(c3) - 48;
        }
        std::cout << "The puzzle is set to " << col << "x" << col << ".\n"; 
    }
    else{
        // Set the col value by default
        col = 3;
        std::cout << "The puzzle is set to 8-Puzzle or 3x3.\n";
    }
    std::cout << "Do you want to set the initial puzzle to start from it?\n";
    c3 = 0; // Use c3 again
    while (!is_answer_char(c3)){
        std::cout << "(Enter y to set, or n to set it random, automatically:)\n";
        std::cin >> c3;
    }
    return 0;
}

bool is_answer_char(char c){
    return (c == 'y' || c == 'Y' || c == 'n' || c == 'N') ? true : false;
}

bool is_yes(char c){
    return (c == 'y' || c == 'Y' ) ? true : false;
}