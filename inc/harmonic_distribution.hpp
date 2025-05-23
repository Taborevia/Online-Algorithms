#ifndef HARMONIC_DISTRIBUTION_HPP
#define HARMONIC_DISTRIBUTION_HPP

#include "distribution.hpp"
#include <vector>
#include <random>

class harmonic_distribution : public distribution{
public:
    explicit harmonic_distribution(int max_value);
    int sample(std::mt19937& rng) const override;

private:
    void compute_probabilities() override;
};

#endif // HARMONIC_DISTRIBUTION_HPP
