#include "mid_project.h"

int run_puzzle(){
    char c1{}, c2{};
    int i1{};
    std::cout << "Started...\n";
    std::cout << "Welcom to Number Puzzle\n";
    std::cout << "Do you want to solve or see?\n";
    while (!is_answer_char(c1)){
        std::cout << "(Enter y to solve a puzzle or n to see how a puzzle is solved:)\n";
        std::cin >> c1;
    }
    std::cout << "The default puzzle is 8-Puzzle which is 3x3.\n";
    while (!is_answer_char(c2)){
        std::cout << "(Enter y to continue or n to change the puzzle:)\n";
        std::cin >> c2;
    }
    if (!is_yes(c2)){
        std::cout << "Specify the puzzle columns or dimention.\n";
        std::cout << "(Enter an integer from 2 to 6 For example if you enter 2 the puzzle is going to be 3x3:)\n";
        while (i1 < 2 || i1 > 6){

        }
    }
}

bool is_answer_char(char c){
    return (c == 'y' || c == 'Y' || c == 'n' || c == 'N') ? true : false;
}

bool is_yes(char c){
    return (c == 'y' || c == 'Y' ) ? true : false;
}