#include "mid_project.h"
#include <list>

int func(int x[]);

int main(int argc, char **argv)
{
    std::cout << "Started...\n";
    // int* x = new int[3];
    int x[3];
    x[0] = 10;
    x[1] = 1;
    x[2] = 2;
    std::cout << func(x) << std::endl;
    std::list<int> y{1, 2, 3};
    std::cout << y.front() << y.front() << std::endl;
    // delete[] x;
    // int n = 3;
    // NumberPuzzle np{ n };
    // np.fill_elements();
    // np.show();

    // // Generating a target
    // int** target = new int*[n];
    // for (int i{}; i < n; i++){
    //     target[i] = new int[n];
    // }
    // for (int i{}; i < n; i++){
    //     for (int j{}; j < n; j++){
    //         target[i][j] = n * i + j + 1;
    //     }
    // }
    // target[n - 1][n - 1] = 1;

    // std::cout << np.is_completed(target) << std::endl;
    // // std::list<int> = new std::list<int>();
    return 0;
}

int func(int x[]){
    return x[0];
}