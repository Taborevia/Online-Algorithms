#include "harmonic_distribution.hpp"
#include <numeric>

harmonic_distribution::harmonic_distribution(int max_value) : distribution(max_value) {
    compute_probabilities();
}

void harmonic_distribution::compute_probabilities() {
    double harmonic_sum = 0.0;
    for (int i = 1; i <= max_value; ++i)
        harmonic_sum += 1.0 / i;

    probabilities.resize(max_value);
    cumulative.resize(max_value);

    double cumulative_sum = 0.0;
    for (int i = 1; i <= max_value; ++i) {
        probabilities[i - 1] = (1.0 / i) / harmonic_sum;
        cumulative_sum += probabilities[i - 1];
        cumulative[i - 1] = cumulative_sum;
    }
}

int harmonic_distribution::sample(std::mt19937& rng) const {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double u = dist(rng);

    // Znajdź odpowiedni przedział
    for (int i = 0; i < max_value; ++i) {
        if (u < cumulative[i])
            return i + 1;
    }
    return max_value;  // Teoretycznie nie powinno się zdarzyć
}
