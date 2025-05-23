#ifndef UNIFORM_DISTRIBUTION_HPP
#define UNIFORM_DISTRIBUTION_HPP

#include "distribution.hpp"
#include <vector>
#include <random>

class uniform_distribution : public distribution{
public:
    explicit uniform_distribution(int max_value);
    int sample(std::mt19937& rng) const override;

private:
    void compute_probabilities() override;
};

#endif 