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
    harmonic_distribution harmonic(100);
    biharmonic_distribution biharmonic(100);
    geometric_distribution geometric(100);
    linked_list list0(0);
    linked_list list1(1);
    linked_list list2(2);
    int random;
    // list1.access(0);
    // list1.access(1);
    // list1.access(2);
    // list1.access(3);
    // list1.access(4);
    // list1.access(3);
    // list1.print();
    std::array<int,100> arr_harmonic={};
    std::array<int,100> arr_biharmonic={};
    std::array<int,100> arr_geometric={};
    int attempts=100000;
    for (int i=0;i<attempts;i++){
        // random = rand(rng);
        // std::cout<<list1.access(random)<<std::endl;
        // list1.print();
        arr_harmonic[harmonic.sample(rng)]++;
        arr_biharmonic[biharmonic.sample(rng)]++;
        arr_geometric[geometric.sample(rng)]++;
        // std::cout<<harmonic.sample(rng)<<" ";
    }
    for (int i=0;i<arr_harmonic.size();i++){
        std::cout<<i<<": "<<float(arr_harmonic[i])/attempts<<std::endl;
    }
    std::cout<<std::endl;
    for (int i=0;i<arr_biharmonic.size();i++){
        std::cout<<i<<": "<<float(arr_biharmonic[i])/attempts<<std::endl;
    }
    std::cout<<std::endl;
    for (int i=0;i<arr_geometric.size();i++){
        std::cout<<i<<": "<<float(arr_geometric[i])/attempts<<std::endl;
    }
}