#include "mid_project.h"
#include <list>

int main(int argc, char **argv)
{
    std::cout << "Started...\n";
    NumberPuzzle np{};
    int puzzle[] = {
        1, 2, 4,
        3, 6, 5,
        7, 0, 8
    };

    // int puzzle[] = {
    //     0, 2, 3,
    //     1, 5, 6,
    //     4, 7, 8
    // };
    NumberPuzzle::Node root{puzzle, 3};
    
    NumberPuzzle::UniformedSearch ui{};
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
    
    std::cout << "\n";
    return 0;
}