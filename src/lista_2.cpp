#include "paging.hpp"
#include "distribution.hpp"
#include "harmonic_distribution.hpp"
#include "biharmonic_distribution.hpp"
#include "geometric_distribution.hpp"
#include <random>
#include <vector>
#include <chrono>
#include <set>
#include <fstream>

int main(){
    // auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    // std::mt19937 rng(static_cast<unsigned>(seed));
    // std::uniform_int_distribution<int> dist(1, 10);
    // harmonic_distribution harmonic(100);
    // for (int k =10;k<20;k+=2){
    //     paging RAND(100,k,4);
    //     float avg = 0;
    //     for(int j = 0;j<100;j++){
    //         int result = 0;
    //         for(int i = 0;i<100000;i++){
    //             int rand= harmonic.sample(rng);
    //             // std::cout<<rand<<std::endl;
    //             result+=RAND.access(rand);
    //         }
    //         avg+=float(result)/100000;
    //     }
    //     std::cout<<avg/100<<" "<<k<<std::endl;
    // }
    
    std::ofstream plik("wyniki_lista_2_geometryczny.txt");
    std::vector<int> input_length = {100, 500, 1000, 5000, 10000, 50000, 100000};
    std::vector<int> n_vector = {20, 30, 40, 50, 60, 70, 80, 90, 100};
    std::vector<std::set<int>> k_vector(n_vector.size());
    for(int i=0;i<n_vector.size();i++){
        for(int j=10;j>=5;j--){
            k_vector.at(i).insert(static_cast<int>(n_vector.at(i)/j));
        }
    }
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 rng(static_cast<unsigned>(seed));
    
    int number_of_inputs=100000;
    for (int n=0;n<n_vector.size();n++){
        std::uniform_int_distribution<int> dist(1, n_vector.at(n));
        geometric_distribution geometric(n_vector.at(n));
        harmonic_distribution harmonic(n_vector.at(n));
        biharmonic_distribution biharmonic(n_vector.at(n));
        for(int k : k_vector.at(n)){
            std::cout<<n<<" "<<k<<std::endl;
            paging FIFO(n_vector.at(n),k,0);
            paging FWF(n_vector.at(n),k,1);
            paging LRU(n_vector.at(n),k,2);
            paging LFU(n_vector.at(n),k,3);
            paging RAND(n_vector.at(n),k,4);
            paging RMA(n_vector.at(n),k,5);
            std::vector<float> avg(6,0);
            for (int i =0;i<100;i++){
                std::vector<int> results(6,0);
                for (int j =0;j<number_of_inputs;j++){
                    int rand = geometric.sample(rng);
                    results.at(0)+=FIFO.access(rand);
                    results.at(1)+=FWF.access(rand);
                    results.at(2)+=LRU.access(rand);
                    results.at(3)+=LFU.access(rand);
                    results.at(4)+=RAND.access(rand);
                    results.at(5)+=RMA.access(rand);
                }
                for (int j =0;j<6;j++){
                    avg.at(j)+=float(results.at(j))/number_of_inputs;
                }
            }
            for (int j =0;j<6;j++){
                plik<<j<<" "<<avg.at(j)/100<<" "<<n_vector.at(n)<<" "<<k<<"\n";
            }
        }
    }
}