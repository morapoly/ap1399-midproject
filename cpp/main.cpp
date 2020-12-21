#include "mid_project.h"

bool func(int &x);

int main(int argc, char **argv)
{
    std::cout << "Started...\n";
    /*
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

    // int puzzle6[] = {
    //     7,   1,  2,  3,  4,  5,
    //     13,  8,  9, 10, 11,  6,
    //     19, 14, 15, 16, 17, 12,
    //     25, 20, 21, 22, 23, 18,
    //     31, 26, 27, 28, 29, 24,
    //      0, 32, 33, 34, 35, 30,        
    // };

    int puzzle6[] = {
        1,   2,  3,  4,  5,  6,
        7,   8,  9, 10, 11, 12,
        13, 14, 15, 16, 17, 18,
        19, 20, 21, 22, 23, 24,
        25, 26, 27, 28, 29, 30,
        31, 32, 33, 34,  0, 35,        
    };
    int p[100];
    for (int i{}; i < 100; i++){
        p[i] = i + 1;
    }
    p[99] = 99;
    p[98] = 0;

    NumberPuzzle::Node root{p, 10};
    // NumberPuzzle::Node root{3};
    
    NumberPuzzle ui{10};
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
    */
    // run_puzzle();
    NumberPuzzle np;
    std::shared_ptr<NumberPuzzle::Node> node;
    node = np.make_random_puzzle(100);
    // node->show();
    return 0;
}

bool func(int &x){
    x ++;
    return x == 10;
}