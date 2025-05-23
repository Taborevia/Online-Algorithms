#include "distribution.hpp"
#include "harmonic_distribution.hpp"
#include "biharmonic_distribution.hpp"
#include "geometric_distribution.hpp"
#include <random>
#include <vector>
#include <chrono>
#include <set>
#include <fstream>
#include <iostream>
#include <memory>

int main(){
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 rng(static_cast<unsigned>(seed));
    
    std::vector<std::unique_ptr<distribution>> distributions;
    std::vector<double> averages = {0,0,0};
    distributions.resize(3);
    distributions.at(0) = std::make_unique<geometric_distribution>(100);    
    distributions.at(1) = std::make_unique<harmonic_distribution>(100);    
    distributions.at(2) = std::make_unique<biharmonic_distribution>(100);    
    for (int i = 0;i<3;i++){
        for (int j = 0;j<100000;j++){
            averages.at(i) += distributions.at(i)->sample(rng);
        }
    }
    for (int i = 0;i<3;i++){
        std::cout<<averages.at(i)/100000<<"\n";
    }
}