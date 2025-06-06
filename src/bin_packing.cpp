#include "bin_packing.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <chrono>
#include <optional>


BinPacking::BinPacking(int bin_capacity, int organization_type) : m_bin_capacity(bin_capacity), m_organization_type(organization_type) {
    m_bins.push_back(1);
    if(organization_type==1){
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        m_rng = std::mt19937(static_cast<unsigned>(seed));
        m_dist = std::uniform_real_distribution<float>(0,1);
    }
}
void BinPacking::add(double value){
    switch (m_organization_type)
    {
    case 0://next fit
        if(m_bins.back()>= value){
            m_bins.back()-=value;
        }else{
            m_bins.push_back(1-value);
        }
        break;
    case 1:{//random fit
        std::vector<int> candidates;
        for (int i =0;i<m_bins.size();i++){
            if(m_bins.at(i)>=value){
                candidates.push_back(i);
            }
        }
        if(!candidates.empty()){
            m_bins.at(candidates.at(ceil(m_dist(m_rng)*candidates.size())-1))-=value;
        }else{
            m_bins.push_back(1-value);
        }
        break;
    }
    case 2:{//first fit
        bool found_bin = false;
        for (auto& i : m_bins){
            if (i>=value){
                i -= value;
                found_bin = true;
                break;
            }
        }
        if(!found_bin){
            m_bins.push_back(1-value);
        }
        break;
    }
    case 3:{//best fit
        std::optional<int> best;
        double best_val=2;
        for(int i = 0;i<m_bins.size();i++){
            if (m_bins.at(i)>=value){
                if (m_bins.at(i)<best_val){
                    best_val=m_bins.at(i);
                    best = i;
                }
            }
        }
        if (best.has_value()){
            m_bins[best.value()] -= value;
        }else{
            m_bins.push_back(1-value);
        }
        break;
    }
    case 4:{//worst fit
        std::optional<int> best;
        double best_val=0;
        for(int i = 0;i<m_bins.size();i++){
            if (m_bins.at(i)>best_val && m_bins.at(i)>=value){
                best_val=m_bins.at(i);
                best = i;
            }
        }
        if (best.has_value()){
            m_bins[best.value()] -= value;
        }else{
            m_bins.push_back(1-value);
        }
        break;
    }
    default:
        break;
    }
}
int BinPacking::get_number_of_bins(){
    return m_bins.size();
}