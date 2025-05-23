#include "geometric_distribution.hpp"
#include <numeric>

geometric_distribution::geometric_distribution(int max_value) : distribution(max_value) {}

void geometric_distribution::compute_probabilities() {
    double geometric_sum = 0.0;
    probabilities.resize(max_value);
    cumulative.resize(max_value);

    double cumulative_sum = 0.0;
    for (int i = 1; i < max_value; ++i) {
        probabilities[i - 1] = (1.0 / pow(2,i));
        cumulative_sum += probabilities[i - 1];
        cumulative[i - 1] = cumulative_sum;
    }
    probabilities[max_value-1] = (1.0/pow(2,max_value-1));
    cumulative_sum += probabilities[max_value-1];
    cumulative[max_value-1] = cumulative_sum;
}

// int geometric_distribution::sample(std::mt19937& rng) const {
//     std::uniform_real_distribution<double> dist(0.0, 1.0);
//     double u = dist(rng);

//     // Znajdź odpowiedni przedział
//     for (int i = 0; i < max_value; ++i) {
//         if (u < cumulative[i])
//             return i + 1;
//     }
//     return max_value;  // Teoretycznie nie powinno się zdarzyć
// }

int geometric_distribution::sample(std::mt19937& rng) const{
    std::bernoulli_distribution ber(0.5);
    int result = 1;
    while (!ber(rng)){
        result++;
    }
    if (result>max_value) result = max_value;
    return result;
}
