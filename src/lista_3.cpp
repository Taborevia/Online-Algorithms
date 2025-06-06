#include "bin_packing.hpp"
#include "distribution.hpp"
#include "uniform_distribution.hpp"
#include "harmonic_distribution.hpp"
#include "biharmonic_distribution.hpp"
#include "geometric_distribution.hpp"
#include "bin_ILP.hpp"
#include <random>
#include <vector>
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>

int main(){
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 rng(static_cast<unsigned>(seed));
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::vector<std::unique_ptr<distribution>> distributions;
    distributions.resize(4);
    distributions.at(0) = std::make_unique<uniform_distribution>(10);
    distributions.at(1) = std::make_unique<geometric_distribution>(10);    
    distributions.at(2) = std::make_unique<harmonic_distribution>(10);    
    distributions.at(3) = std::make_unique<biharmonic_distribution>(10);    
    int n =100000;
    for(int l = 0;l<distributions.size();l++){
        std::string filename = "wyniki_lista_3_" + std::to_string(l);
        std::ofstream plik(filename);
        std::vector<double> averages(5,0);
        for(int k = 0;k<n;k++){
            // if (k%100000==0) std::cout<<k<<std::endl;
            std::vector<BinPacking> bins;
            for(int i =0;i<5;i++){
                bins.emplace_back(1,i);
            }
            std::vector<double> elements;
            while (elements.size()<100){
                double rand = dist(rng);
                int number_of_repititions = distributions.at(l)->sample(rng);
                for(int i =0;i<number_of_repititions;i++){
                    elements.push_back(rand);
                }
            }
            elements.resize(100);
            double sum=0;
            for (double& i : elements){
                sum+=i;
                for(auto& bin : bins){
                    bin.add(i);
                }
            }
            for (int i =0;i<bins.size();i++){
                averages.at(i)+=(bins.at(i).get_number_of_bins()/ceil(sum));
            }
            // std::cout<<std::endl<<"ILP: "<<solveBinPacking(elements,bin_0.get_number_of_bins());
        }
        for (int i =0;i<averages.size();i++){
            plik<<averages.at(i)/n<<std::endl;
        }
        plik.close();
    }
}