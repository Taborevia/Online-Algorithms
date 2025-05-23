#ifndef BIHARMONIC_DISTRIBUTION_HPP
#define BIHARMONIC_DISTRIBUTION_HPP

#include "distribution.hpp"
#include <vector>
#include <random>

class biharmonic_distribution : public distribution{
public:
    explicit biharmonic_distribution(int max_value);
    int sample(std::mt19937& rng) const override;

private:
    void compute_probabilities() override;
};

#endif 