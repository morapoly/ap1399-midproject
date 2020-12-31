#include "mid_project.h"

int main(int argc, char **argv)
{
    bool b{true};
    while (b){
        b = run_puzzle();
        system("clear");
    }
    return 0;
}
