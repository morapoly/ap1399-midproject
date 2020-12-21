#ifndef NUMBERPUZZLE_H
#define NUMBERPUZZLE_H

#include <iostream>
#include <iomanip>
#include <deque>
#include <memory>

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
        bool goal_test() const;
        bool goal_test(int* goal_puzzle) const;
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

    NumberPuzzle();
    ~NumberPuzzle();
    NumberPuzzle(int c);
    void set_goal_puzzle();
    void set_goal_puzzle(int* p);
    std::deque<std::shared_ptr<Node>> breadth_first_search(std::shared_ptr<Node> root);
    bool contains(std::deque<std::shared_ptr<Node>> list, std::shared_ptr<Node> c);
    void path_trace(std::deque<std::shared_ptr<Node>> &path, std::shared_ptr<Node> node);
    private:
    int c{3};   // Number of columns
    int n{c * c};
    int* goal_puzzle;
};

#endif