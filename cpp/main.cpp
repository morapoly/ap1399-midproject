#include "mid_project.h"

int main(int argc, char **argv)
{
    char c{};
    std::cout << "Started...\n";
    std::cout << "Welcom to Number Puzzle\n";
    std::cout << "Do you want to solve or see?\n";
    while (c != 'y' && c != 'Y' && c != 'n' && c != 'N'){
        std::cout << "(Enter y to solve a puzzle or n to see how a puzzle is solved.)\n";
        std::cin >> c;
    }
    if (c == 'y' || c == 'Y'){

    }
    else{

    }
    NumberPuzzle np{};
    // int puzzle[] = {  // compatible with gp1
    //     1, 2, 4,
    //     3, 0, 5,
    //     7, 6, 8
    // };

    // int puzzle[] = {
    //     3, 1, 2,
    //     5, 0, 8,
    //     4, 6, 7, 
    // };

    int puzzle[] = {       // compatible with gp2
        4, 1, 3,
        7, 0, 6,
        5, 2, 8 
    };

    int gp1[] = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8 
    };

    int gp2[] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 0 
    };

    int puzzle2[] = {
        3, 1,
        0, 2
    };

    int gp3[] = {
        1, 2,
        3, 0
    };

    int puzzle4[] = {
        5,  1,  3,  4,
        0,  2,  7,  8,
        9,  6, 10, 11,
        13,14, 15, 12
    };

    int gp4[] = {
        1,  2,  3,  4,
        5,  6,  7,  8,
        9, 10, 11, 12,
        13,14, 15,  0
    };

    NumberPuzzle::Node root{puzzle4, 4};
    // NumberPuzzle::Node root{3};
    
    NumberPuzzle ui{4};
    ui.set_goal_puzzle(gp4);
    std::deque<std::shared_ptr<NumberPuzzle::Node>> sol = ui.breadth_first_search(std::make_shared<NumberPuzzle::Node>(root));
    std::cout << "Ended...\n"; 

    if (sol.size() > 0){
        sol = std::deque<std::shared_ptr<NumberPuzzle::Node>>(sol.rbegin(),sol.rend());
        for (size_t i{}; i < sol.size(); i++){
            sol[i]->show();
        }
    }
    else{
        std::cout << "No path to solution is found...\n"; 
    }
    
    return 0;
}