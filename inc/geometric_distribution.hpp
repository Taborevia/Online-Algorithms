#ifndef geometric_DISTRIBUTION_HPP
#define geometric_DISTRIBUTION_HPP

#include "distribution.hpp"
#include <vector>
#include <random>

class geometric_distribution : public distribution {
public:
    explicit geometric_distribution(int max_value);
    int sample(std::mt19937& rng) const override;

private:
    void compute_probabilities();
};

#endif // geometric_DISTRIBUTION_HPP
