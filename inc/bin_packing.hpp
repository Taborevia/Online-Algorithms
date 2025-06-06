#ifndef BP_H
#define BP_H

#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <chrono>

class BinPacking {
public:
    double m_bin_capacity;
    int m_organization_type;
    std::vector<double> m_bins;
    std::mt19937 m_rng;
    std::uniform_real_distribution<float> m_dist;
    BinPacking(int bin_capacity, int organization_type); //0 - without organization, 1 - Move to front, 2-transpose,3-count
    void add(double value);
    int get_number_of_bins();
};

#endif