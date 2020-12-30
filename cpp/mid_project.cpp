#include "mid_project.h"

bool run_puzzle(){
    char c1{}, c2{}, c3{}, c4{}, c5{}, c6{}, c7{};
    int col{}, n{}, moves{}, max_depth{};
    int* initial_puzzle;
    int* goal_puzzle;
    std::ifstream fs;

    std::cout << "\033[1;40m"; // set backgroung color to black
    std::cout << "\033[1;35m"; // magenta bold text
    std::cout << "------------------------\n";
    std::cout << "Welcom to Number Puzzle.\n";
    std::cout << "------------------------\n";
    std::cout << "\033[0m\n"; // rest to default

    std::cout << "Do you want to solve or see?\n";
    std::cout << "\033[1;36m"; // cyan bold text
    while (!is_answer_char(c1)){
        std::cout << "(Enter y to solve a puzzle, or n to see how a puzzle is solved:)\n";
        std::cin >> c1;
    }
    std::cout << "\033[0m\n"; // rest to default
    std::cout << "The default puzzle is 8-Puzzle which is 3x3, Do you want to continue?\n";
    std::cout << "\033[1;36m"; // cyan bold text
    while (!is_answer_char(c2)){
        std::cout << "(Enter y to continue, or n to change the puzzle:)\n";
        std::cin >> c2;
    }
    std::cout << "\033[0m\n"; // rest to default
    if (!is_yes(c2)){
        std::cout << "Specify the puzzle columns or dimention.\n";
        std::cout << "\033[1;36m"; // cyan bold text
        while (col < 2 || col > 6 || !std::isdigit(c3)){
            std::cout << "(Enter an integer from 2 to 6 For example if you enter 4 the puzzle will be 4x4:)\n";
            std::cin >> c3;
            col = int(c3) - 48;
        }
        std::cout << "\033[0m\n"; // rest to default
        std::cout << "The puzzle is set to " << col << "x" << col << ".\n"; 
    }
    else{
        // Set the col value by default
        col = 3;
        std::cout << "The puzzle is set to 8-Puzzle or 3x3.\n";
    }

    n = col * col;
    
    // Showing goal puzzle 
    std::cout << "The goal puzzle is:\n";
    goal_puzzle = new int[n];
    NumberPuzzle::Node goal_node{goal_puzzle, col};
    goal_node.set_puzzle();
    goal_node.copy_puzzle(goal_puzzle, goal_node.puzzle);
    goal_node.show();

    std::cout << "Do you want to continue?\n";
    c3 = 0; // Use c3 again
    std::cout << "\033[1;36m"; // cyan bold text
    while (!is_answer_char(c3)){
        std::cout << "(Enter y to continue or n to set the goal puzzle:)\n";
        std::cin >> c3;
    }
    std::cout << "\033[0m\n"; // rest to default
    if (!is_yes(c3)){
        // User set the goal puzzle
        std::cout << "Do you want to enter the puzzle elements here?\n";
        std::cout << "\033[1;36m"; // cyan bold text
        while (!is_answer_char(c4)){
            std::cout << "(Enter y to enter elements in terminal window or n to set it from file:)\n";
            std::cin >> c4;
        }
        std::cout << "\033[0m\n"; // rest to default
        if (is_yes(c4)){
            // User sets elements in terminal window
            std::cout << "\033[1;34m"; // blue bold text
            std::cout << "You must enter elements in correct way:\n";
            std::cout << "1. Use 0 insted of the blank element.\n";
            std::cout << "2. Use numbers from 1 to " << n - 1 << ".\n";
            std::cout << "3. Don't use duplicate numbers.\n";
            std::cout << "\033[0m\n"; // rest to default
            std::cout << "Enter elements:\n";
            for (int i{}; i < n; i++){
                std::cin >> goal_puzzle[i];
            }
            std::cout << "Goal puzzle is set!\n";
        }
        else{
            // User sets elements from file
            std::cout << "Input.txt exists in h folder, replace your txt file as same name and format or overwrite inside file.\n";
            std::cout << "\033[1;36m"; // cyan bold text
            std::cout << "(Enter y if you are done:)\n";
            std::cout << "\033[0m\n"; // rest to default
            
            c4 = 0; // Use c4 again
            while (!(c4 == 'y' || c4 == 'Y')){
                std::cin >> c4;
            }

            fs.open("./h/input.txt");
            if (fs.is_open()){
                for (int i{}; i < n; i++){
                    fs >> goal_puzzle[i];
                }
                std::cout << "The goal puzzle set to:\n";
                goal_node.set_puzzle(goal_puzzle);
                goal_node.show();
            }
            else{
                std::cout << "\033[1;31m"; // red bold text
                std::cout << "File not found!\n";
                std::cout << "\033[0m\n"; // rest to default
                std::cout << "The goal puzzle set default!\n";
            }
            fs.close();
        }
        goal_node.set_puzzle(goal_puzzle);
    }

    std::shared_ptr<NumberPuzzle::Node> initial_node = std::make_shared<NumberPuzzle::Node>(col);
    initial_puzzle = new int[n];
    initial_node->set_puzzle(goal_puzzle);
    initial_node->copy_puzzle(initial_puzzle, goal_puzzle);

    std::cout << "Do you want to set the initial puzzle which is started from it?\n";
    std::cout << "\033[1;36m"; // cyan bold text
    while (!is_answer_char(c5)){
        std::cout << "(Enter y to set, or n to be set random, automatically:)\n";
        std::cin >> c5;
    }
    std::cout << "\033[0m\n"; // rest to default
    if (is_yes(c5)){
        // User sets the initial puzzle
        std::cout << "Do you want to enter the initial puzzle elements here?\n";
        std::cout << "\033[1;36m"; // cyan bold text
        while (!is_answer_char(c6)){
            std::cout << "(Enter y to enter elements in terminal window or n to set it from file:)\n";
            std::cin >> c6;
        }
        std::cout << "\033[1;35m"; // magneta bold text
        std::cout << "Please remember, you must enter elements in correct way.\n";
        std::cout << "(Important: your puzzle should be solvable base on the goal puzzle.)\n";
        std::cout << "\033[0m\n"; // rest to default
        if (is_yes(c6)){
            // User sets elements in terminal window
            std::cout << "Enter elements:\n";
            for (int i{}; i < n; i++){
                std::cin >> initial_puzzle[i];
            }
            std::cout << "Initial puzzle is set!\n";
        }
        else{
            // User sets elements from file
            std::cout << "Input.txt exists in h folder, replace your txt file as same name and format or overwrite inside file.\n";
            std::cout << "\033[1;36m"; // cyan bold text
            std::cout << "(Enter y if you are done:)\n";
            std::cout << "\033[0m\n"; // rest to default
            
            c4 = 0; // Use c4 again
            while (!(c4 == 'y' || c4 == 'Y')){
                std::cin >> c4;
            }

            fs.open("./h/input.txt");
            if (fs.is_open()){
                for (int i{}; i < n; i++){
                    fs >> initial_puzzle[i];
                }
                std::cout << "The initial puzzle set to:\n";
                initial_node->set_puzzle(initial_puzzle);
                initial_node->show();
            }
            else{
                std::cout << "\033[1;31m"; // red bold text
                std::cout << "File not found!\n";
                std::cout << "\033[0m\n"; // rest to default
                std::cout << "The initial puzzle didn't set!\n";
            }
            fs.close();
        }
    }
    else{
        // It is going to set random
        std::cout << "How many moves do you want the randomizer moves?\n";
        std::cout << "\033[1;36m"; // cyan bold text
        while (moves < 10){
            std::cout << "(Enter an integer greater equal than 10, great numbers make it harder to solve:)\n";
            std::cin >> moves;
        }
        std::cout << "\033[0m\n"; // rest to default

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
        
        // Going to see how the puzzle is solved
        std::cout << "It's going to solve puzzle.\n";
        std::cout << "Do you want to be going to solved by BFS algorithm or DFS?\n";

        c1 = 0; // Use c1 again
        std::cout << "\033[1;36m"; // cyan bold text
        while (!is_answer_char(c1)){
            std::cout << "(Enter y for BFS or n for DFS:)\n";
            std::cin >> c1;
        }
        std::cout << "\033[0m\n"; // rest to default

        NumberPuzzle np{col};
        np.set_goal_puzzle(goal_puzzle);
        initial_node->set_puzzle(initial_puzzle);

        if (is_yes(c1)){
            auto solution = np.breadth_first_search(initial_node);
            if (solution.size() > 0){
                // reversing
                solution = std::deque<std::shared_ptr<NumberPuzzle::Node>>(solution.rbegin(), solution.rend());
                for (size_t i{}; i < solution.size(); i++){
                    std::cout << "Move " << i << std::endl;
                    solution[i]->show();
                }
            }
            else{
                std::cout << "\033[1;31m"; // red bold text
                std::cout << "No path to solution is found...\n"; 
                std::cout << "\033[0m\n"; // rest to default
            }
        }
        else{
            std::cout << "\033[1;36m"; // cyan bold text
            while (max_depth < 30){
                std::cout << "(Enter an integer greater equal than 30 for max depth:)\n";
                std::cin >> max_depth;
            }
            std::cout << "\033[0m\n"; // rest to default
            auto solution = np.depth_first_search(initial_node, max_depth);
            if (solution.size() > 0){
                for (size_t i{}; i < solution.size(); i++){
                    std::cout << "Move " << i << std::endl;
                    solution[i]->show();
                }
            }
            else{
                std::cout << "\033[1;31m"; // red bold text
                std::cout << "No path to solution is found...\n"; 
                std::cout << "\033[0m\n"; // rest to default
            }
        }
    }
    else{
        // User is going to solve the puzzle
        initial_node->set_puzzle(initial_puzzle); // For sake of mohkamkari!
        std::cout << "You are going to solve the puzzle.\n";
        initial_node->show();
        std::cout << "\033[1;36m"; // cyan bold text
        std::cout << "(Use w to move up, s to move down, a to move left & d to move right.)\n";
        while (!initial_node->goal_test(goal_puzzle)){
            while (c7 != 'w' && c7 != 'W' && c7 != 's' && c7 != 'S' && c7 != 'a' && c7 != 'A' && c7 != 'd' && c7 != 'D' && c7 != 'e' && c7 != 'E'){
                std::cout << "w a s d to move or e to left:\n";
                std::cin >> c7;
            }
            if (c7 == 'w' || c7 == 'W'){
                initial_node->move_to_up();
                initial_node->show();
            }
            else if (c7 == 's' || c7 == 'S'){
                initial_node->move_to_down();
                initial_node->show();
            }
            else if (c7 == 'a' || c7 == 'A'){
                initial_node->move_to_left();
                initial_node->show();
            }
            else if (c7 == 'd' || c7 == 'D'){
                initial_node->move_to_right();
                initial_node->show();
            }
            else{
                break;
            }
            c7 = 0;
        }
        std::cout << "\033[0m\n"; // rest to default
        if (initial_node->goal_test()){
            std::cout << "\033[1;35m"; // magneta bold text
            std::cout << "****************\n";
            std::cout << "Congratulations!\n";
            std::cout << "****************\n";
            std::cout << "\033[0m\n"; // rest to default
            std::cout << "You solved the puzzle.\n";
        }
        else{
            std::cout << "You left!\n";
        }
    }
    std::cout << "Do you want to run puzzle again?\n";
    
    // Use c7 again
    c7 = 0;
    std::cout << "\033[1;36m"; // cyan bold text
    while (!is_answer_char(c7)){
        std::cout << "(Enter y to run again and n to exit.\n";
        std::cin >> c7;
    }
    std::cout << "\033[0m\n"; // rest to default
    if (is_yes(c7)){
        return true;
    }
    else{
        return false;
    }
}

bool is_answer_char(char c){
    return (c == 'y' || c == 'Y' || c == 'n' || c == 'N') ? true : false;
}

bool is_yes(char c){
    return (c == 'y' || c == 'Y' ) ? true : false;
}