#ifndef PG_H
#define PG_H

#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <chrono>

class paging {
public:
    int m_number_of_pages;
    int m_number_of_fast_pages;
    std::vector<int> m_fast_pages;
    std::vector<int> m_pages_frequency;
    int m_organization_type;
    std::vector<int> m_timestamps;
    int m_clock_counter;
    std::mt19937 rng;
    std::uniform_real_distribution<float> dist;
    std::vector<bool> m_marks_vector;
    int m_marks_counter;
    paging(int number_of_pages,int number_of_fast_pages,int organization_type); //0 - without organization, 1 - Move to front, 2-transpose,3-count
    int access(int value);
    void print();
};

#endif