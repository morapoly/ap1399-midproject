#include "mid_project.h"

int run_puzzle(){
    char c1{}, c2{}, c3{}, c4{}, c5{}, c6{}, c7{};
    int col{}, n{}, moves{};
    int* initial_puzzle;
    int* goal_puzzle;
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

    n = col * col;
    
    std::cout << "The goal puzzle is:\n";
    
    // Showing goal puzzle 
    goal_puzzle = new int[n];
    std::shared_ptr<NumberPuzzle::Node> goal_node = std::make_shared<NumberPuzzle::Node>(goal_puzzle, col);
    goal_node->set_puzzle();
    goal_node->copy_puzzle(goal_puzzle, goal_node->puzzle);
    goal_node->show();

    std::cout << "Do you want to continue?\n";
    c3 = 0; // Use c3 again
    while (!is_answer_char(c3)){
        std::cout << "(Enter y to continue or n to set the goal puzzle:)\n";
        std::cin >> c3;
    }
    if (!is_yes(c3)){
        // User set the goal puzzle
        std::cout << "Do you want to enter the puzzle elements here?\n";
        while (!is_answer_char(c4)){
            std::cout << "(Enter y to enter elements in terminal window or n to set it from file:)\n";
            std::cin >> c4;
        }
        if (is_yes(c4)){
            // User sets elements in terminal window
            std::cout << "You must enter elements in correct way:\n";
            std::cout << "1. Use 0 insted of the blank element.\n";
            std::cout << "2. Use numbers from 1 to " << n - 1 << ".\n";
            std::cout << "3. Don't use duplicate numbers.\n";
            std::cout << "Enter elements:\n";
            for (int i{}; i < n; i++){
                std::cin >> goal_puzzle[i];
            }
            std::cout << "Goal puzzle is set!\n";
        }
        else{
            // User sets elements from file
        }
        goal_node->set_puzzle(goal_puzzle);
    }

    std::shared_ptr<NumberPuzzle::Node> initial_node = std::make_shared<NumberPuzzle::Node>(col);

    std::cout << "Do you want to set the initial puzzle which is started from it?\n";
    while (!is_answer_char(c5)){
        std::cout << "(Enter y to set, or n to be set it random, automatically:)\n";
        std::cin >> c5;
    }
    if (is_yes(c5)){
        // User sets the initial puzzle
        std::cout << "Do you want to enter the initial puzzle elements here?\n";
        while (!is_answer_char(c6)){
            std::cout << "(Enter y to enter elements in terminal window or n to set it from file:)\n";
            std::cin >> c6;
        }
        if (is_yes(c6)){
            // User sets elements in terminal window
            std::cout << "Please remember, you must enter elements in correct way.\n";
            std::cout << "(Important: your puzzle should be solvable base on the goal puzzle.)\n";
            std::cout << "Enter elements:\n";
            initial_puzzle = new int[n];
            for (int i{}; i < n; i++){
                std::cin >> initial_puzzle[i];
            }
            std::cout << "Initial puzzle is set!\n";
        }
        else{
            // User sets elements from file
        }

        // initial_node->set_puzzle(initial_puzzle);
    }
    else{
        // It is going to set random
        std::cout << "How many moves do you want the randomizer moves?\n";
        while (moves < 10){
            std::cout << "(Enter an integer greater equal than 10, great numbers make it harder to solve:)\n";
            std::cin >> moves;
        }

        initial_puzzle = new int[n];
        NumberPuzzle temp{col};
        temp.set_goal_puzzle(goal_puzzle);
        initial_node->copy_puzzle(initial_puzzle, temp.make_random_puzzle(moves)->puzzle);
        initial_node->set_puzzle(initial_puzzle);

        std::cout << "The initial puzzle is set to:\n";
        initial_node->show();
    }

    // Starting operations
    if (!is_yes(c1)){
        
        // Going to see how the puzzle is solved using BFS algorithm
        std::cout << "It's going to solve puzzle.\n";
        NumberPuzzle np{col};
        np.set_goal_puzzle(goal_puzzle);
        auto solution = np.breadth_first_search(std::make_shared<NumberPuzzle::Node>(initial_puzzle, col));
        if (solution.size() > 0){
            solution = std::deque<std::shared_ptr<NumberPuzzle::Node>>(solution.rbegin(), solution.rend());
            for (size_t i{}; i < solution.size(); i++){
                std::cout << "Move " << i << std::endl;
                solution[i]->show();
            }
        }
        else{
            std::cout << "No path to solution is found...\n"; 
        }
    }
    else{
        // User is going to solve the puzzle
        initial_node->set_puzzle(initial_puzzle); // For sake of mohkamkari!
        std::cout << "You are going to solve the puzzle.\n";
        
    }

    return 0;
}

bool is_answer_char(char c){
    return (c == 'y' || c == 'Y' || c == 'n' || c == 'N') ? true : false;
}

bool is_yes(char c){
    return (c == 'y' || c == 'Y' ) ? true : false;
}