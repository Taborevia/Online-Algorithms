#include "biharmonic_distribution.hpp"
#include <numeric>
#include <math.h>

biharmonic_distribution::biharmonic_distribution(int max_value) : distribution(max_value) {
    compute_probabilities();
}

void biharmonic_distribution::compute_probabilities() {
    double biharmonic_sum = 0.0;
    for (int i = 1; i <= max_value; ++i)
        biharmonic_sum += 1.0 / pow(i,2);

    probabilities.resize(max_value);
    cumulative.resize(max_value);

    double cumulative_sum = 0.0;
    for (int i = 1; i <= max_value; ++i) {
        probabilities[i - 1] = (1.0 / pow(i,2)) / biharmonic_sum;
        cumulative_sum += probabilities[i - 1];
        cumulative[i - 1] = cumulative_sum;
    }
}

int biharmonic_distribution::sample(std::mt19937& rng) const {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double u = dist(rng);

    // Znajdź odpowiedni przedział
    for (int i = 0; i < max_value; ++i) {
        if (u < cumulative[i])
            return i + 1;
    }
    return max_value;  // Teoretycznie nie powinno się zdarzyć
}
