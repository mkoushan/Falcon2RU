#include "dice.hpp"
#include <random>

int roll(const std::vector<std::pair<int, double>>& probabilities) {
    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
  
    // Generate a random value to determine the outcome
    double rand_val = std::generate_canonical<double, 10>(gen);

    // Calculate the cumulative probability
    double cumulative_prob = 0.0;
    for (const auto& pair : probabilities) {
        cumulative_prob += pair.second;
        if (rand_val < cumulative_prob) {
            return pair.first;
        }
    }

    // This point should never be reached if probabilities sum to 1
    return -1; // Handle error
}
