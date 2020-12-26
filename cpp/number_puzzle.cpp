#include "number_puzzle.h"

// Node methods
NumberPuzzle::Node::Node(){
    col = 3;
    n = col * col;
    set_puzzle();
}

NumberPuzzle::Node::~Node(){
    puzzle = nullptr;
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

bool NumberPuzzle::Node::goal_test() const{
    int* goal_puzzle = new int[n];
    for (int i{}; i < n; i++){
        goal_puzzle[i] = i + 1;
    }
    goal_puzzle[n - 1] = 0;
    return goal_test(goal_puzzle);
}

bool NumberPuzzle::Node::goal_test(int* goal_puzzle) const{
    bool is_goal{1};
    for (int i{}; i < n; i++){
        is_goal = is_goal && ( (puzzle[i] == goal_puzzle[i]) ? 1 : 0 );
    }
    return is_goal;
}

void NumberPuzzle::Node::set_x(){
    for (int i{}; i < n; i++){
        if (puzzle[i] == 0){
            x = i;
        }
    }
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
        child->parent = std::make_shared<Node>(*this);
        
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
        child->parent = std::make_shared<Node>(*this);

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
        child->parent = std::make_shared<Node>(*this);

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
        child->parent = std::make_shared<Node>(*this);

        return true;
    }
    else{
        return false;
    }
}

bool NumberPuzzle::Node::move_to_right(){
    int temp;
    set_x();
    if (x % col < col - 1){
        temp = puzzle[x + 1];
        puzzle[x + 1] = puzzle[x];
        puzzle[x] = temp;
        set_x();
        return true;
    }
    else{
        return false;
    }
}

bool NumberPuzzle::Node::move_to_left(){
    int temp;
    set_x();
    if (x % col > 0){
        temp = puzzle[x - 1];
        puzzle[x - 1] = puzzle[x];
        puzzle[x] = temp;
        set_x();
        return true;
    }
    else{
        return false;
    }
}

bool NumberPuzzle::Node::move_to_up(){
    int temp;
    set_x();
    if (x - col >= 0){
        temp = puzzle[x - col];
        puzzle[x - col] = puzzle[x];
        puzzle[x] = temp;
        set_x();
        return true;
    }
    else{
        return false;
    }
}

bool NumberPuzzle::Node::move_to_down(){
    int temp;
    set_x();
    if (x + col < n){
        temp = puzzle[x + col];
        puzzle[x + col] = puzzle[x];
        puzzle[x] = temp;
        set_x();
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
            if (c == x){
                std::cout << std::setw(4) << " " << " ";
            }
            else{
                std::cout << std::setw(4) << puzzle[c] << " ";
            }
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
    set_x();
    move_to_right(puzzle, x);
    move_to_left(puzzle, x);
    move_to_up(puzzle, x);
    move_to_down(puzzle, x);
}

void NumberPuzzle::Node::expand_node(std::deque<std::shared_ptr<Node>> open_list, std::deque<std::shared_ptr<Node>> closed_list){
    set_x();
    
    // move to right
    if (x % col < col - 1){
        int* pc = new int[n];
        copy_puzzle(pc,puzzle);
        
        int temp = pc[x + 1];
        pc[x + 1] = pc[x];
        pc[x] = temp;

        std::shared_ptr<Node> child = std::make_shared<Node>(pc, col);
        if (!exists(open_list, child) && !exists(closed_list, child)){
            children.push_back(child);
            child->parent = std::make_shared<Node>(*this);
            return;
        }
    }

    // move to left
    if (x % col > 0){
        int* pc = new int[n];
        copy_puzzle(pc,puzzle);
        
        int temp = pc[x - 1];
        pc[x - 1] = pc[x];
        pc[x] = temp;

        std::shared_ptr<Node> child = std::make_shared<Node>(pc, col);
        if (!exists(open_list, child) && !exists(closed_list, child)){
            children.push_back(child);
            child->parent = std::make_shared<Node>(*this);
            return;
        }
    }

    // move to up
    if (x - col > 0){
        int* pc = new int[n];
        copy_puzzle(pc,puzzle);
        
        int temp = pc[x - col];
        pc[x - col] = pc[x];
        pc[x] = temp;

        std::shared_ptr<Node> child = std::make_shared<Node>(pc, col);
        if (!exists(open_list, child) && !exists(closed_list, child)){
            children.push_back(child);
            child->parent = std::make_shared<Node>(*this);
            return;
        }
    }

    // move to down
    if (x + col < n){
        int* pc = new int[n];
        copy_puzzle(pc,puzzle);
        
        int temp = pc[x + col];
        pc[x + col] = pc[x];
        pc[x] = temp;

        std::shared_ptr<Node> child = std::make_shared<Node>(pc, col);
        if (!exists(open_list, child) && !exists(closed_list, child)){
            children.push_back(child);
            child->parent = std::make_shared<Node>(*this);
            return;
        }
    }
}

bool NumberPuzzle::Node::exists(std::deque<std::shared_ptr<Node>> list, std::shared_ptr<Node> c){
    bool contains = false;
    for (size_t i{}; i < list.size(); i++){
        if (list[i]->is_same_puzzle(c->puzzle)){
            contains = true;
        }
    }
    return contains;
}

NumberPuzzle::NumberPuzzle(){
    c = 3;
    n = c * c;
    set_goal_puzzle();
}

NumberPuzzle::~NumberPuzzle(){
    goal_puzzle = nullptr;
}

NumberPuzzle::NumberPuzzle(int c){
    this->c = c;
    n = c * c;
    set_goal_puzzle();
}

void NumberPuzzle::set_goal_puzzle(){
    goal_puzzle = new int[n];
    for (int i{}; i < n; i++){
        goal_puzzle[i] = i + 1;
    }
    goal_puzzle[n - 1] = 0;
}

void NumberPuzzle::set_goal_puzzle(int* p){
    goal_puzzle = new int[n];
    for (int i{}; i < n; i++){
        goal_puzzle[i] = p[i];
    }
}

std::shared_ptr<NumberPuzzle::Node> NumberPuzzle::make_random_puzzle(int moves){
    std::shared_ptr<Node> output = std::make_shared<Node>(goal_puzzle, c);
    srand(time(0));
    bool b[4] = {0, 0, 0, 0};
    int count{};
    auto random_number {rand()};
    while (count < moves){
        if (random_number % 4 == 0){
            b[0] = output->move_to_right();
        }
        else if (random_number % 4 == 1){
            b[1] = output->move_to_left();
        }
        else if (random_number % 4 == 2){
            b[2] = output->move_to_up();
        }
        else{
            b[3] = output->move_to_down();
        }
        random_number = rand();
        count++;
        if (!(b[0] || b[1] || b[2] || b[3])){
            count--;
        }
        b[0] = b[1] = b[2] = b[3] = 0;
    }
    return output;
}

std::deque<std::shared_ptr<NumberPuzzle::Node>> NumberPuzzle::breadth_first_search(std::shared_ptr<Node> root){
    auto start = std::chrono::high_resolution_clock::now();

    if (root->goal_test(goal_puzzle)){
        return std::deque<std::shared_ptr<Node>>{root};
    }
    
    std::deque<std::shared_ptr<Node>> path_to_solution{};
    std::deque<std::shared_ptr<Node>> open_list{};
    std::deque<std::shared_ptr<Node>> closed_list{};
    
    open_list.push_back(root);
    bool goal_reached{false};
    
    while(open_list.size() > 0 && !goal_reached){
        auto between = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed{between - start};
        std::cout << std::setw(4) << int(elapsed.count()) << " sec elapsed, (solving... please wait.)\r";
        std::shared_ptr<Node> current_node = open_list.front();
        closed_list.push_back(current_node);
        open_list.pop_front();

        current_node->expand_node();

        for (size_t i{}; i < current_node->children.size(); i++){
            std::shared_ptr<Node> current_child = current_node->children[i];
            
            if (current_child->goal_test(goal_puzzle)){
                std::cout << "*************\n";
                std::cout << "Goal reached!" << std::endl;
                std::cout << "*************\n";
                goal_reached = true;
                // Tracing path
                path_trace(path_to_solution, current_child);
            }

            if (!contains(open_list, current_child) && !contains(closed_list, current_child)){
                open_list.push_back(current_child);
            }
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed{finish - start};
    std::cout << "\n>> Elapsed time: " << elapsed.count() * 1000 << " ms\n\n";
    return path_to_solution;
}
/*
std::deque<std::shared_ptr<NumberPuzzle::Node>> NumberPuzzle::depth_first_search(std::shared_ptr<Node> root){

    // if root is goal_node, it returns
    if (root->goal_test(goal_puzzle)){
        return std::deque<std::shared_ptr<Node>>{root};
    }
    
    std::deque<std::shared_ptr<Node>> path_to_solution{};
    std::deque<std::shared_ptr<Node>> open_list{};
    std::deque<std::shared_ptr<Node>> closed_list{};

    bool goal_reached{false};
    
    open_list.push_back(root);
    std::shared_ptr<Node> current_node = open_list.front();

    while (open_list.size() > 0 && !goal_reached){
        current_node->expand_node();
        current_node->show();

        if (current_node->children.size() > 0){
            std::shared_ptr<Node> current_child = current_node->children[0];
            // for (size_t i{1}; i < current_node->children.size(); i++){
            //     if (contains(closed_list,current_child) || contains(open_list,current_child)){
            //         current_child = current_node->children[i];
            //     }
            // }
            if (contains(closed_list, current_child) || contains(open_list, current_child)){
                // if (!contains(closed_list, current_node)){
                //     closed_list.push_back(current_node);
                //     open_list.pop_back();
                // }
                if (!contains(closed_list, open_list.back())){
                    closed_list.push_back(open_list.back());
                    open_list.pop_back();
                }
                if (current_node != root){
                    current_node = current_node->parent;
                }
            }
            else{
                if (current_child->goal_test(goal_puzzle)){
                    std::cout << "*************\n";
                    std::cout << "Goal reached!" << std::endl;
                    std::cout << "*************\n";
                    goal_reached = true;

                    // Tracing path
                    path_trace(path_to_solution, current_child);
                }
                else{
                    if (!contains(open_list,current_node)){
                        open_list.push_back(current_node);
                    }
                    current_node = current_child;
                    // else{
                    //     closed_list.push_back(open_list.back());
                    //     open_list.pop_back();
                    //     current_node = open_list.back();
                    // }
                }
            }
        }
        else{
            if (!contains(closed_list, open_list.back())){
                closed_list.push_back(open_list.back());
            }
            open_list.pop_back();
            current_node = current_node->parent;

        }
    }
    return path_to_solution;
}
*/
std::deque<std::shared_ptr<NumberPuzzle::Node>> NumberPuzzle::depth_first_search(std::shared_ptr<Node> root){
    
    // if root is goal_node, it returns
    if (root->goal_test(goal_puzzle)){
        return std::deque<std::shared_ptr<Node>>{root};
    }
    
    std::deque<std::shared_ptr<Node>> path_to_solution{};
    std::deque<std::shared_ptr<Node>> open_list{};
    std::deque<std::shared_ptr<Node>> closed_list{};

    bool goal_reached{false};
    
    open_list.push_back(root);
    std::shared_ptr<Node> current_node = open_list.front();

    int count{};
    while (open_list.size() > 1 && !goal_reached){
        if (count < 1000){
            current_node->expand_node(open_list, closed_list);
            count++;   
        }
        // current_node->expand_node();
        // current_node->show();

        std::shared_ptr<Node> current_child;
        
        for (size_t i{}; i < current_node->children.size(); i++){
            if (current_node->children[i]->goal_test(goal_puzzle)){
                std::cout << "*************\n";
                std::cout << "Goal reached! Fast check" << std::endl;
                std::cout << "*************\n";
                std::cout << "open_list lentgh: " << open_list.size() << "\n";
                goal_reached = true;

                // Tracing path
                path_trace(path_to_solution, current_node->children[i]);
                return path_to_solution;
            }
            
        }
        for (size_t i{}; i < current_node->children.size(); i++){
            if (!contains(open_list, current_node->children[i]) && !contains(closed_list, current_node->children[i])){
                current_child = current_node->children[i];
                break;
            }
        }
        
        // the state that we are in a loop
        if (!current_child){
            std::cout << open_list.size() <<" open\n";
            std::cout << closed_list.size() <<" closed\n";
            if (!contains(closed_list, open_list.back())){
                closed_list.push_back(open_list.back());
                open_list.pop_back();
                current_node = open_list.back();
            }
            else{
                std::cout << "you are fucked up!\n";
            }
        }
        else if (current_child->goal_test(goal_puzzle)){
            std::cout << "*************\n";
            std::cout << "Goal reached!" << std::endl;
            std::cout << "*************\n";
            std::cout << "open_list lentgh: " << open_list.size() << "\n";
            goal_reached = true;

            // Tracing path
            path_trace(path_to_solution, current_child);
        }
        else{
            if (contains(open_list, current_child)){
                std::cout << "you are fucked up!\n";
            }
            open_list.push_back(current_child);
            current_node = open_list.back();
        }
    }

    return path_to_solution;
}

bool NumberPuzzle::contains(std::deque<std::shared_ptr<Node>> list, std::shared_ptr<Node> c){
    bool contains = false;
    for (size_t i{}; i < list.size(); i++){
        if (list[i]->is_same_puzzle(c->puzzle)){
            contains = true;
        }
    }
    return contains;
}

void NumberPuzzle::path_trace(std::deque<std::shared_ptr<Node>> &path, std::shared_ptr<Node> node){
    std::cout << "Tracing path...\n";
    std::shared_ptr<NumberPuzzle::Node> current = node;
    path.push_back(current);

    while (current->parent != nullptr){
        current = current->parent;
        path.push_back(current);
    }
}