#include "mid_project.h"

bool func(int &x);

int main(int argc, char **argv)
{
    std::cout << "Started...\n";

    // int puzzle[] = {       // compatible with goal
    //     8, 2, 3,
    //     6, 7, 4,
    //     1, 5, 0
    // };

    // int goal[] = {
    //     1, 2, 3,
    //     4, 5, 6,
    //     7, 8, 0 
    // };

    // NumberPuzzle::Node root{puzzle, 3};
    // // NumberPuzzle::Node root{3};
    
    // NumberPuzzle ui{3};
    // ui.set_goal_puzzle(goal);
    // std::deque<std::shared_ptr<NumberPuzzle::Node>> sol = ui.breadth_first_search(std::make_shared<NumberPuzzle::Node>(root));
    // std::cout << "Ended...\n"; 

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
    // bool b{true};
    // while (b){
    //     b = run_puzzle();
    // }
    std::ifstream fs;
    fs.open("./stuff/input.txt");
    int p[9];
    int i{};
    fs >> p[i];
    if (fs.is_open()){
        // while (!fs.eof()){
        //     fs >> p[i];
        //     i++;
        // }
    }
    else{
        std::cout << "File not found.\n";
    }
    fs.close();
    std::cout << p[0] << std::endl;
    return 0;
}

bool func(int &x){
    x ++;
    return x == 10;
}