#include "number_puzzle.h"

// for dfs time measuring
auto dfs_start = std::chrono::high_resolution_clock::now();
int dfs_count{};

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

std::shared_ptr<NumberPuzzle::Node> NumberPuzzle::Node::get_right_child(){
    set_x();
    if (x % col < col - 1){
        int* pc = new int[n];
        copy_puzzle(pc,puzzle);
        
        int temp = pc[x + 1];
        pc[x + 1] = pc[x];
        pc[x] = temp;

        set_x();
        std::shared_ptr<Node> child = std::make_shared<Node>(pc, col);
        children.push_back(child);
        child->parent = std::make_shared<Node>(*this);
        
        return child;
    }
    else{
        return nullptr;
    }
}

std::shared_ptr<NumberPuzzle::Node> NumberPuzzle::Node::get_left_child(){
    set_x();
    if (x % col > 0){
        int* pc = new int[n];
        copy_puzzle(pc,puzzle);

        int temp = pc[x - 1];
        pc[x - 1] = pc[x];
        pc[x] = temp;
        
        set_x();
        std::shared_ptr<Node> child = std::make_shared<Node>(pc, col);
        children.push_back(child);
        child->parent = std::make_shared<Node>(*this);

        return child;
    }
    else{
        return nullptr;
    }
}

std::shared_ptr<NumberPuzzle::Node> NumberPuzzle::Node::get_up_child(){
    set_x();
    if (x - col >= 0){
        int* pc = new int[n];
        copy_puzzle(pc,puzzle);

        int temp = pc[x - col];
        pc[x - col] = pc[x];
        pc[x] = temp;

        set_x();
        std::shared_ptr<Node> child = std::make_shared<Node>(pc, col);
        children.push_back(child);
        child->parent = std::make_shared<Node>(*this);

        return child;
    }
    else{
        return nullptr;
    }
}

std::shared_ptr<NumberPuzzle::Node> NumberPuzzle::Node::get_down_child(){
    set_x();
    if (x + col < n){
        int* pc = new int[n];
        copy_puzzle(pc,puzzle);

        int temp = pc[x + col];
        pc[x + col] = pc[x];
        pc[x] = temp;

        set_x();
        std::shared_ptr<Node> child = std::make_shared<Node>(pc, col);
        children.push_back(child);
        child->parent = std::make_shared<Node>(*this);

        return child;
    }
    else{
        return nullptr;
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
    std::cout << "\033[1;33m"; // yellow bold text
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
    std::cout << "\033[0m"; // reset to defau;t
}

bool NumberPuzzle::Node::is_same_puzzle(int* p) const{
    for (int i{}; i < n; i++){
        if (puzzle[i] != p[i]){
            return false;
        }
    }
    return true;
}

int NumberPuzzle::Node::find_element(int element){
    for (int i{}; i < n; i++){
        if (puzzle[i] == element){
            return i;
        }
    }
    return -1;
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
    grid = nullptr;
    moves = nullptr;
    best_moves = nullptr;
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
    
    int count{1};
    while(open_list.size() > 0 && !goal_reached){
        auto between = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed{between - start};
        if (elapsed.count() >= count){
            std::cout << "\033[1;32m"; // green bold text
            std::cout << "\033[A\033[2K"; // remove last line
            std::cout << std::setw(4) << count << "s >> solving... please wait!\n";
            count++;
        }
        std::shared_ptr<Node> current_node = open_list.front();
        closed_list.push_back(current_node);
        open_list.pop_front();

        current_node->expand_node();

        for (size_t i{}; i < current_node->children.size(); i++){
            std::shared_ptr<Node> current_child = current_node->children[i];
            
            if (current_child->goal_test(goal_puzzle)){
                std::cout << "\033[A\033[2K"; // remove last line
                std::cout << "\033[1;35m"; // magneta bold text
                std::cout << "\n*************\n";
                std::cout << "Goal reached!" << std::endl;
                std::cout << "*************\n";
                std::cout << "\033[0m\n"; // rest to default
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
    std::cout << "\033[1;32m"; // green bold text
    std::cout << "\n>> Elapsed time: " << elapsed.count() * 1000 << " ms\n\n";
    std::cout << "\033[0m\n"; // rest to default
    return path_to_solution;
}

std::deque<std::shared_ptr<NumberPuzzle::Node>> NumberPuzzle::depth_first_search(std::shared_ptr<Node> root, int max_depth){
    std::deque<std::shared_ptr<Node>> path_to_solution{};
    this->max_depth = max_depth;

    grid = new int*[c];
    for (int i{}; i < c; i++){
        grid[i] = new int[c];
    }

    moves = new int[max_depth];
    best_moves = new int[max_depth];
    best_depth = max_depth;

    // seting grid to initial puzzle
    for (int i{}; i < c; i++){
        for (int j{}; j < c; j++){
            grid[i][j] = root->puzzle[i * c + j];
        }
    }

    // finding the blank element or zero element
    int origin_x{}, origin_y{};
    for (int i{}; i < c; i++){
        for (int j{}; j < c; j++){
            if (grid[i][j] == 0){
                origin_x = i;
                origin_y = j;
                break;
            }
        }
    }

    // starting search
    auto start = std::chrono::high_resolution_clock::now();
    dfs_start = start;
    dfs_count = 1;

    search_dfs(origin_x, origin_y, 0, -1, -1);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed{finish - start};
    std::cout << "\033[1;32m"; // green bold text
    std::cout << "\n>> Elapsed time: " << elapsed.count() * 1000 << " ms\n\n";
    std::cout << "\033[0m\n"; // rest to default

    int* temp_puzzle = new int[n];
    root->copy_puzzle(temp_puzzle, root->puzzle);
    path_to_solution.push_back(std::make_shared<Node>(temp_puzzle, c));

    std::cout << "Tracing path...\n";
    for (int i{}; i < best_depth; i++){
        std::shared_ptr<Node> temp_node{std::make_shared<Node>(temp_puzzle, c)};
        temp_node->set_x();
        temp_puzzle[temp_node->find_element(best_moves[i])] = 0;
        temp_puzzle[temp_node->x] = best_moves[i];
        temp_node->set_puzzle(temp_puzzle);
        path_to_solution.push_back(temp_node);
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

void NumberPuzzle::search_dfs(int zero_x, int zero_y, int depth, int played_x, int played_y){
    static bool succes{false};

    // cutoff
    if (depth >= best_depth){
        return;
    }

    if (depth != 0){
        moves[depth - 1] = grid[played_x][played_y];
    }

    // checking goal
    if (is_correct()){
        // std::cout << "Goal reached with depth: " << std::setw(5) << depth << "!\n" ;
        if (!succes){
            std::cout << "\033[A\033[2K"; // remove last line
            std::cout << "\033[1;35m"; // magneta bold text
            std::cout << "*************\n";
            std::cout << "Goal reached!\n";
            std::cout << "*************\n";
            std::cout << "\033[0m\n"; // rest to default
            succes = true;
        }

        best_depth = depth;

        for (int i{}; i < depth; i++){
            best_moves[i] = moves[i];
        }

    }

    // time measuring
    auto between = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed{between - dfs_start};
    if (elapsed.count() >= dfs_count){
        std::cout << "\033[1;32m"; // green bold text
        std::cout << "\033[A\033[2K"; // remove last line
        std::cout << std::setw(4) << dfs_count << "s >> solving... please wait!\n";
        dfs_count++;
    }

    // moving
    int x1{zero_x + 1};
    int y1{zero_y};

    int x2{zero_x - 1};
    int y2{zero_y};

    int x3{zero_x};
    int y3{zero_y + 1};

    int x4{zero_x};
    int y4{zero_y - 1};

    // removing the repeating moves
    if (x1 == played_x && y1 == played_y) x1 = y1 = -1;
    if (x2 == played_x && y2 == played_y) x2 = y2 = -1;
    if (x3 == played_x && y3 == played_y) x3 = y3 = -1;
    if (x4 == played_x && y4 == played_y) x4 = y4 = -1;

    if (x1 >= 0 && y1 >= 0 && x1 < c && y1 < c){
        grid[zero_x][zero_y] = grid[x1][y1];
        grid[x1][y1] = 0;
        
        search_dfs(x1, y1, depth + 1, zero_x, zero_y);

        grid[x1][y1] = grid[zero_x][zero_y];
        grid[zero_x][zero_y] = 0;
    }

    if (x2 >= 0 && y2 >= 0 && x2 < c && y2 < c){
        grid[zero_x][zero_y] = grid[x2][y2];
        grid[x2][y2] = 0;
        
        search_dfs(x2, y2, depth + 1, zero_x, zero_y);

        grid[x2][y2] = grid[zero_x][zero_y];
        grid[zero_x][zero_y] = 0;
    }

    if (x3 >= 0 && y3 >= 0 && x3 < c && y3 < c){
        grid[zero_x][zero_y] = grid[x3][y3];
        grid[x3][y3] = 0;
        
        search_dfs(x3, y3, depth + 1, zero_x, zero_y);

        grid[x3][y3] = grid[zero_x][zero_y];
        grid[zero_x][zero_y] = 0;
    }

    if (x4 >= 0 && y4 >= 0 && x4 < c && y4 < c){
        grid[zero_x][zero_y] = grid[x4][y4];
        grid[x4][y4] = 0;
        
        search_dfs(x4, y4, depth + 1, zero_x, zero_y);

        grid[x4][y4] = grid[zero_x][zero_y];
        grid[zero_x][zero_y] = 0;
    }

}

bool NumberPuzzle::is_correct(){
    for (int i{}; i < c; i++){
        for (int j{}; j < c; j++){
            if (grid[i][j] != goal_puzzle[i * c + j]){
                return false;
            }
        }
    }
    return true;
}