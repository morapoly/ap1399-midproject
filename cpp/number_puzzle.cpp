#include "number_puzzle.h"

NumberPuzzle::Node::Node(){
    col = 3;
    n = col * col;
    set_puzzle();
}

NumberPuzzle::Node::~Node(){
    delete[] puzzle;
}

NumberPuzzle::Node::Node(int c){
    col = c;
    n = c * c;
    set_puzzle();
}

NumberPuzzle::Node::Node(int* p,int c){
    col = c;
    n = c * c;
    set_puzzle(p);
}

NumberPuzzle::Node::Node(Node* node){
    n = node->n;
    col = node->col;
    x = node->x;
    parent = node->parent;
    children = node->children;
    copy_puzzle(puzzle, node->puzzle);
}

void NumberPuzzle::Node::set_puzzle(){
    puzzle = new int[n];  
    for (int i{}; i < n; i++){
        puzzle[i] = i + 1;
    }
    puzzle[n - 1] = 0;
    x = n - 1;
}

void NumberPuzzle::Node::set_puzzle(int* p){
    puzzle = new int[n];  
    for (int i{}; i < n; i++){
        puzzle[i] = p[i];
        if (p[i] == 0){
            x = i;
        }
    }
}

bool NumberPuzzle::Node::goal_test(){
    int* goal_puzzle = new int[n];
    for (int i{}; i < n; i++){
        goal_puzzle[i] = i + 1;
    }
    goal_puzzle[n - 1] = 0;
    return goal_test(goal_puzzle);
}

bool NumberPuzzle::Node::goal_test(int* goal_puzzle){
    bool is_goal{1};
    for (int i{}; i < n; i++){
        is_goal = is_goal && ( (puzzle[i] == goal_puzzle[i]) ? 1 : 0 );
    }
    return is_goal;
}

bool NumberPuzzle::Node::move_to_right(int* p,int i){
    if (i % col < col - 1){
        int* pc = new int[n];
        copy_puzzle(pc,p);

        int temp = pc[i + 1];
        pc[i + 1] = pc[i];
        pc[i] = temp;

        std::shared_ptr<Node> child = std::make_shared<Node>(pc, col);
        children.push_back(child);
        child->parent = std::make_shared<Node>(this);

        return true;
    }
    else{
        return false;
    }
}

bool NumberPuzzle::Node::move_to_left(int* p,int i){
    if (i % col > 0){
        int* pc = new int[n];
        copy_puzzle(pc,p);

        int temp = pc[i - 1];
        pc[i - 1] = pc[i];
        pc[i] = temp;

        std::shared_ptr<Node> child = std::make_shared<Node>(pc, col);
        children.push_back(child);
        child->parent = std::make_shared<Node>(this);

        return true;
    }
    else{
        return false;
    }
}

bool NumberPuzzle::Node::move_to_up(int* p,int i){
    if (i - col >= 0){
        int* pc = new int[n];
        copy_puzzle(pc,p);

        int temp = pc[i - col];
        pc[i - col] = pc[i];
        pc[i] = temp;

        std::shared_ptr<Node> child = std::make_shared<Node>(pc, col);
        children.push_back(child);
        child->parent = std::make_shared<Node>(this);

        return true;
    }
    else{
        return false;
    }
}

bool NumberPuzzle::Node::move_to_down(int* p,int i){
    if (i + col < n){
        int* pc = new int[n];
        copy_puzzle(pc,p);

        int temp = pc[i + col];
        pc[i + col] = pc[i];
        pc[i] = temp;

        std::shared_ptr<Node> child = std::make_shared<Node>(pc, col);
        children.push_back(child);
        child->parent = std::make_shared<Node>(this);

        return true;
    }
    else{
        return false;
    }
}

void NumberPuzzle::Node::copy_puzzle(int* pc, int* p){
    for (int i{}; i < n; i++){
        pc[i] = p[i];
    }
}

void NumberPuzzle::Node::show() const{
    int c{};
    std::cout << std::endl;
    for (int i{}; i < col; i++){
        for (int j{}; j < col; j++){
            std::cout << std::setw(col) << puzzle[c] << " ";
            c++;
        }
        std::cout << std::endl << std::endl;
    }
}

bool NumberPuzzle::Node::is_same_puzzle(int* p) const{
    for (int i{}; i < n; i++){
        if (puzzle[i] != p[i]){
            return false;
        }
    }
    return true;
}

void NumberPuzzle::Node::expand_node(){
    for (int i{}; i < n; i++){
        if (puzzle[i] == 0){
            x = i;
        }
    }

    move_to_right(puzzle, x);
    move_to_left(puzzle, x);
    move_to_up(puzzle, x);
    move_to_down(puzzle, x);
}

std::list<std::shared_ptr<NumberPuzzle::Node>> NumberPuzzle::UniformedSearch::breadth_first_search(std::shared_ptr<Node> root){
    std::list<std::shared_ptr<Node>> path_to_solution{};
    std::list<std::shared_ptr<Node>> opened_list{};
    std::list<std::shared_ptr<Node>> closed_list{};
    
    opened_list.push_back(root);
    bool goal_reached{false};
    while(opened_list.size() > 0 && !goal_reached){
        std::shared_ptr<Node> current_node = opened_list.front();
        closed_list.push_back(current_node);
        opened_list.pop_front();

        current_node->expand_node();

    //     for (int i{}; i < current_node->children.size(); i++){
    //         std::shared_ptr<Node> current_child = current_node->children[i];
    //         if (current_child->goal_test()){
    //             std::cout << "Goal reached..." << std::endl;
    //             goal_reached = true;
    //         }
    //     }
    // }

    return path_to_solution;
}

NumberPuzzle::NumberPuzzle(){
    Node();
}

// NumberPuzzle::~NumberPuzzle(){
//     for (int i{}; i < n; i++){
//         delete[] elements[i];
//     }
//     delete[] elements;
// }

NumberPuzzle::NumberPuzzle(int c){
    this->c = c;
}

// void NumberPuzzle::fill_elements(){
//     elements = new int*[n];
//     for (int i{}; i < n; i++){
//         elements[i] = new int[n];
//     }
//     for (int i{}; i < n; i++){
//         for (int j{}; j < n; j++){
//             elements[i][j] = n * i + j + 1;
//         }
//     }
//     elements[n - 1][n - 1] = 0;
// }

// void NumberPuzzle::show() const{
//     // std::cout << std::endl;
//     // for (int i{}; i < n; i++){
//     //     for (int j{}; j < n; j++){
//     //         std::cout << std::setw(n) << elements[i][j] << " ";
//     //     }
//     //     std::cout << std::endl << std::endl;
//     // }

// }

// bool NumberPuzzle::is_completed(int** goal_state) const{
//     bool result{ 1 };
//     for (int i{}; i < n; i++){
//         for (int j{}; j < n; j++){
//             result = result && ( (elements[i][j] == goal_state[i][j]) ? 1 : 0 );
//         }
//     }
//     return result;
// }