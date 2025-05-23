#ifndef DISTRIBUTION_HPP
#define DISTRIBUTION_HPP

#include <vector>
#include <random>

class distribution {
public:
    explicit distribution(int max_value) : max_value(max_value) {}
    virtual int sample(std::mt19937& rng) const=0;

protected:
    int max_value;
    std::vector<double> probabilities;
    std::vector<double> cumulative;

    virtual void compute_probabilities()=0;
};

#endif 