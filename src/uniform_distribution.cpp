#include "uniform_distribution.hpp"
#include <numeric>

uniform_distribution::uniform_distribution(int max_value) : distribution(max_value) {
}

void uniform_distribution::compute_probabilities() {
}

int uniform_distribution::sample(std::mt19937& rng) const {
    std::uniform_int_distribution<int> dist(1,max_value);
    return dist(rng);  
}
