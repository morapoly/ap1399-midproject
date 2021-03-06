#ifndef NUMBERPUZZLE_H
#define NUMBERPUZZLE_H

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <deque>
#include <memory>
#include <random>
#include <chrono>

class NumberPuzzle{
    public:
    class Node{
        public:
        int* puzzle;
        int x{};    // Index of zero element
        int col{3};
        int n{col * col};        
        std::shared_ptr<Node> parent;
        std::deque<std::shared_ptr<Node>> children;

        Node();
        ~Node();
        Node(int c);
        Node(int* p,int c);
        Node(Node* node);
        void set_puzzle();
        void set_puzzle(int* p);
        bool goal_test() const;
        bool goal_test(int* goal_puzzle) const;
        void set_x();
        bool move_to_right(int* p,int i);
        bool move_to_left(int* p,int i);
        bool move_to_up(int* p,int i);
        bool move_to_down(int* p,int i);
        bool move_to_right();
        bool move_to_left();
        bool move_to_up();
        bool move_to_down();
        void copy_puzzle(int* pc,int* p);
        void show() const;
        bool is_same_puzzle(int* p) const;
        int find_element(int element);
        void expand_node();
    };

    NumberPuzzle();
    ~NumberPuzzle();
    NumberPuzzle(int c);
    void set_goal_puzzle();
    void set_goal_puzzle(int* p);
    std::shared_ptr<Node> make_random_puzzle(int moves = 10);
    // BFS
    std::deque<std::shared_ptr<Node>> breadth_first_search(std::shared_ptr<Node> root, int max_depth = 100);
    bool contains(std::deque<std::shared_ptr<Node>> list, std::shared_ptr<Node> c);
    void path_trace(std::deque<std::shared_ptr<Node>> &path, std::shared_ptr<Node> node);
    // DFS
    std::deque<std::shared_ptr<Node>> depth_first_search(std::shared_ptr<Node> root, int max_depth = 100);
    void search_dfs(int zero_x, int zero_y, int depth, int played_x, int played_y);
    bool is_correct();
    
    private:
    int c{3};   // Number of columns
    int n{c * c};
    int max_depth;
    int* goal_puzzle;
    
    // just for DFS
    int** grid;
    int* moves;
    int* best_moves;
    int best_depth;
};

#endif