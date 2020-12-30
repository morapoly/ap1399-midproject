#include "mid_project.h"
#include <chrono>
#include <stdlib.h>

int main(int argc, char **argv)
{
    
    std::cout << "Started...\n";
    
    // int puzzle[] = {       // compatible with goal
    //     0, 1, 3,
    //     5, 2, 6,
    //     4, 7, 8 
    // };

    // int goal[] = {
    //     1, 2, 3,
    //     4, 5, 6,
    //     7, 8, 0
    // };

    // NumberPuzzle::Node root{puzzle, 3};
    // // // NumberPuzzle::Node root{3};
    
    // NumberPuzzle ui{3};
    // ui.set_goal_puzzle(goal);
    // std::deque<std::shared_ptr<NumberPuzzle::Node>> sol = ui.depth_first_search(std::make_shared<NumberPuzzle::Node>(root));
    // std::cout << "Ended...\n\n"; 

    // if (sol.size() > 0){
    //     sol = std::deque<std::shared_ptr<NumberPuzzle::Node>>(sol.rbegin(),sol.rend());
    //     for (size_t i{}; i < sol.size(); i++){
    //         sol[i]->show();
    //     }
    // }
    // else{
    //     std::cout << "No path to solution is found...\n"; 
    // }
    
    // std::cout << "Random puzzle: \n";
    // NumberPuzzle np;
    // np.set_goal_puzzle(goal);
    // std::shared_ptr<NumberPuzzle::Node> node;
    // node = np.make_random_puzzle(100);
    // node->show();
    
    bool b{true};
    while (b){
        b = run_puzzle();
    }
    // auto start = std::chrono::high_resolution_clock::now();
    // int x{};
    // while (x < 100000){
    //     x++;
    // }
    // auto finish = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> elapsed = finish - start;
    // std::cout << "Elapsed time: " << elapsed.count()*1000000 << " ms " << std::endl;
    return 0;
}