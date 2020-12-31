#include "mid_project.h"

int main()
{
    bool b{true};
    while (b){
        b = run_puzzle();
        system("clear");
    }
    return 0;
}