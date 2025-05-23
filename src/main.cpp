#include "linked_list.hpp"
#include "harmonic_distribution.hpp"
#include "biharmonic_distribution.hpp"
#include "geometric_distribution.hpp"
#include <random>
#include <array>
#include <chrono>
int main(){
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 rng(static_cast<unsigned>(seed));
    std::uniform_int_distribution<int> rand(0,10);
    linked_list list0(0);
    linked_list list1(1);
    linked_list list2(2);
    linked_list list3(3);
    int random;
    for (int i=0;i<100;i++){
        random = rand(rng);

        std::cout<<random<<" "<<list3.access(random)<<std::endl;
        list3.print();
    }
}