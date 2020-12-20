#ifndef NUMBERPUZZLE_H
#define NUMBERPUZZLE_H

#include <iostream>
#include <iomanip>
#include <deque>
#include <memory>
#include <vector>

class NumberPuzzle{
    public:
    class Node{
        public:
        
        int* puzzle;
        int x{};    // Index of zero element
        int col{3};
        int n{col * col};
        
        Node();
        ~Node();
        Node(int c);
        Node(int* p,int c);
        Node(Node* node);
        void set_puzzle();
        void set_puzzle(int* p);
        bool goal_test();
        bool goal_test(int* goal_puzzle);
        bool move_to_right(int* p,int i);
        bool move_to_left(int* p,int i);
        bool move_to_up(int* p,int i);
        bool move_to_down(int* p,int i);
        void copy_puzzle(int* pc,int* p);
        void show() const;
        bool is_same_puzzle(int* p) const;
        void expand_node();
        std::shared_ptr<Node> parent;
        std::deque<std::shared_ptr<Node>> children;
    
    };
    class UniformedSearch{
        public:
        UniformedSearch() = default;
        ~UniformedSearch() = default;
        std::deque<std::shared_ptr<NumberPuzzle::Node>> breadth_first_search(std::shared_ptr<Node> root);
        bool contains(std::deque<std::shared_ptr<NumberPuzzle::Node>> list, std::shared_ptr<NumberPuzzle::Node> c);
        void path_trace(std::deque<std::shared_ptr<NumberPuzzle::Node>> &path, std::shared_ptr<NumberPuzzle::Node> node);
    };

    NumberPuzzle();
    ~NumberPuzzle() = default;
    NumberPuzzle(int c);
    
    private:
    int c{3};   // Number of columns
    // int m{9};
    // int** elements;
    // void fill_elements();
    // void show() const;
    // bool is_completed(int** goal_state) const;
};

#endif