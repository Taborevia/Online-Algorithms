#include "linked_list.hpp"
#include "harmonic_distribution.hpp"
#include "biharmonic_distribution.hpp"
#include "geometric_distribution.hpp"
#include <random>
#include <array>
#include <fstream>
#include <chrono>
int main(){
    std::array<int,7> attempts = {100, 500, 1000, 5000, 10000, 50000, 100000};
    std::ofstream plik("wyniki_wykres.txt");
    int n = 100000;
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 rng(static_cast<unsigned>(seed));
    std::uniform_int_distribution<int> dist(1, 100);
    harmonic_distribution harmonic(100);
    biharmonic_distribution biharmonic(100);
    geometric_distribution geometric(100);
    linked_list list0(0);
    linked_list list1(1);
    linked_list list2(2);
    linked_list list3(3);
    int random;
    std::vector<int> average_cost_of_harmonic(16,0);
    std::vector<linked_list> linked_lists;
    for(int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            linked_lists.push_back(linked_list(i));
        }
    }
    for (int i=0;i<n;i++){
        for(int j=0;j<4;j++){
            average_cost_of_harmonic[4*j]+=linked_lists[4*j].access(dist(rng));
            average_cost_of_harmonic[(4*j)+1]+=linked_lists[(4*j)+1].access(harmonic.sample(rng));
            average_cost_of_harmonic[(4*j)+2]+=linked_lists[(4*j)+2].access(biharmonic.sample(rng));
            average_cost_of_harmonic[(4*j)+3]+=linked_lists[(4*j)+3].access(geometric.sample(rng));
        }
        // for (int val : attempts) {
        // if((i+1) == val){
            for(int j=0;j<16;j++){
                plik<<i+1<<" "<<float(average_cost_of_harmonic[j])/float(i+1)<<std::endl;
            }
        // }
        // }
    }
}